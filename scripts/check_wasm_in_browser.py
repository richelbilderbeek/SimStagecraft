#!/usr/bin/env python3
"""Check that the WebAssembly version of SimStagecraft starts in a browser.

Serves the built website, opens the app in headless Chromium,
waits for Qt to start, then fails if the page reported an error.

Usage:
  pip install playwright && playwright install --with-deps chromium
  python3 scripts/check_wasm_in_browser.py site
"""
import functools
import http.server
import sys
import threading
import time

from playwright.sync_api import sync_playwright


def main(site_dir):
    handler = functools.partial(http.server.SimpleHTTPRequestHandler, directory=site_dir)
    server = http.server.ThreadingHTTPServer(("127.0.0.1", 0), handler)
    threading.Thread(target=server.serve_forever, daemon=True).start()
    url = f"http://127.0.0.1:{server.server_address[1]}/app/SimStagecraft.html"

    messages = []
    errors = []
    with sync_playwright() as p:
        browser = p.chromium.launch()
        page = browser.new_page(viewport={"width": 1024, "height": 768})
        page.on("console", lambda m: messages.append(f"{m.type}: {m.text}"))
        page.on("pageerror", lambda e: errors.append(str(e)))
        page.goto(url)
        # Wait for Qt to create its screen
        started = False
        for _ in range(60):
            if page.evaluate("() => document.querySelector('.qt-screen, canvas') !== null"):
                started = True
                break
            time.sleep(1)
        # Let the menu run for a while, its timer animates the background
        time.sleep(5)
        # Start the level selection, then a level
        page.mouse.click(512, 384)
        page.keyboard.press("s")
        time.sleep(2)
        page.keyboard.press("s")
        time.sleep(5)
        page.screenshot(path="wasm_screenshot.png")
        browser.close()
    server.shutdown()

    print("Console messages:")
    for m in messages:
        print("  " + m)
    if not started:
        print("FAIL: Qt did not start")
        return 1
    fatal = errors + [m for m in messages
        if "abort" in m.lower() or "exception" in m.lower() or "assertion" in m.lower()]
    if fatal:
        print("FAIL: errors in the page:")
        for e in fatal:
            print("  " + e)
        return 1
    print("OK: SimStagecraft started in the browser")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1] if len(sys.argv) > 1 else "site"))
