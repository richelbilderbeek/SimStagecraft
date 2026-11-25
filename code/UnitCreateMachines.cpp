//---------------------------------------------------------------------------
#include "UnitFormCdPlayer.h"
#include "UnitFormDimblockV3.h"
#include "UnitFormEasyAmp.h"
#include "UnitFormMdPlayer.h"
#include "UnitFormOctlet.h"
#include "UnitFormPar64.h"
#include "UnitFormRcf322A.h"
#include "UnitFormRcfEvent3000.h"
#include "UnitFormShureSm58.h"
#include "UnitFormSimpleShine1.h"
#include "UnitFormSimpleShine2.h"
#include "UnitFormSimpleSound1.h"
#include "UnitFormSimpleSound2.h"
#include "UnitFormSimpleSound3.h"
#include "UnitFormSimpleSound4.h"
#include "UnitFormTransitionPieceJackMaleTwoCinchFemale.h"
#include "UnitFormTriplet.h"
#include "UnitFormWallSocket220.h"
#include "UnitFormWallSocketPower.h"
#include "UnitFormSimStagecraftMain.h"
//---------------------------------------------------------------------------
#include "UnitCreateMachines.h"
//---------------------------------------------------------------------------
std::vector<std::shared_ptr<FormMachine> > CreateMachines(
  FormSimStagecraftMain * const formParent,
  const int level)
{
  std::vector<std::shared_ptr<FormMachine> > machines;

  switch (level)
  {
    case 1:
    {
      std::shared_ptr<FormMachine> m1(
          new FormWallSocket220(formParent));
      std::shared_ptr<FormMachine> m2(
          new FormPar64(formParent));
      machines.push_back(m1);
      machines.push_back(m2);
    }
    break;
    case 2:
    {
      std::shared_ptr<FormMachine> wallSocket220(new FormWallSocket220(formParent));
      std::shared_ptr<FormMachine> speaker(new FormRcf322A(formParent));
      std::shared_ptr<FormMachine> mic(new FormShureSm58(formParent));
      machines.push_back(mic);
      machines.push_back(speaker);
      machines.push_back(wallSocket220);
    }
    break;
    case 3:
    {
      std::shared_ptr<FormMachine> wallSocket220(new FormWallSocket220(formParent));
      std::shared_ptr<FormMachine> speaker1(new FormRcf322A(formParent));
      std::shared_ptr<FormMachine> speaker2(new FormRcf322A(formParent));
      std::shared_ptr<FormMachine> mic(new FormShureSm58(formParent));
      std::shared_ptr<FormMachine> triplet(new FormTriplet(formParent));
      std::shared_ptr<FormMachine> soundTable(new FormSimpleSound1(formParent));
      machines.push_back(speaker1);
      machines.push_back(mic);
      machines.push_back(speaker2);
      machines.push_back(wallSocket220);
      machines.push_back(soundTable);
      machines.push_back(triplet);
    }
    break;
    case 4:
    {
      std::shared_ptr<FormMachine> dimmerpack(new FormDimblockV3(formParent));
      std::shared_ptr<FormMachine> lighttable(new FormSimpleShine1(formParent));
      std::shared_ptr<FormMachine> wallSocketPower(new FormWallSocketPower(formParent));
      std::shared_ptr<FormMachine> wallSocket220(new FormWallSocket220(formParent));
      std::shared_ptr<FormMachine> par64_1(new FormPar64(formParent));
      std::shared_ptr<FormMachine> par64_2(new FormPar64(formParent));
      std::shared_ptr<FormMachine> par64_3(new FormPar64(formParent));
      std::shared_ptr<FormMachine> par64_4(new FormPar64(formParent));
      std::shared_ptr<FormMachine> par64_5(new FormPar64(formParent));
      machines.push_back(wallSocketPower);
      machines.push_back(dimmerpack);
      machines.push_back(wallSocket220);
      machines.push_back(par64_1);
      machines.push_back(lighttable);
      machines.push_back(par64_2);
      machines.push_back(par64_3);
      machines.push_back(par64_4);
      machines.push_back(par64_5);
    }
    break;
    case 5:
    {
      std::shared_ptr<FormMachine> wallSocket220(new FormWallSocket220(formParent));
      std::shared_ptr<FormMachine> speaker1(new FormRcf322A(formParent));
      std::shared_ptr<FormMachine> speaker2(new FormRcf322A(formParent));
      std::shared_ptr<FormMachine> mic1(new FormShureSm58(formParent));
      std::shared_ptr<FormMachine> mic2(new FormShureSm58(formParent));
      std::shared_ptr<FormMachine> triplet(new FormTriplet(formParent));
      std::shared_ptr<FormMachine> soundTable(new FormSimpleSound2(formParent));
      machines.push_back(mic1);
      machines.push_back(triplet);
      machines.push_back(mic2);
      machines.push_back(speaker1);
      machines.push_back(soundTable);
      machines.push_back(speaker2);
      machines.push_back(wallSocket220);
    }
    break;
    case 6:
    {
      std::shared_ptr<FormMachine> wallSocket220(new FormWallSocket220(formParent));
      std::shared_ptr<FormMachine> mic1(new FormShureSm58(formParent));
      std::shared_ptr<FormMachine> speaker1(new FormRcf322A(formParent));
      std::shared_ptr<FormMachine> triplet(new FormTriplet(formParent));
      std::shared_ptr<FormMachine> soundTable3(new FormSimpleSound3(formParent));
      machines.push_back(mic1);
      machines.push_back(speaker1);
      machines.push_back(wallSocket220);
      machines.push_back(triplet);
      machines.push_back(soundTable3);
    }
    break;
    case 7:
    {
      std::shared_ptr<FormMachine> wallSocket220(new FormWallSocket220(formParent));
      std::shared_ptr<FormMachine> mic1(new FormShureSm58(formParent));
      std::shared_ptr<FormMachine> mic2(new FormShureSm58(formParent));
      std::shared_ptr<FormMachine> mic3(new FormShureSm58(formParent));
      std::shared_ptr<FormMachine> speaker1(new FormRcf322A(formParent));
      std::shared_ptr<FormMachine> speaker2(new FormRcf322A(formParent));
      std::shared_ptr<FormMachine> speaker3(new FormRcf322A(formParent));
      std::shared_ptr<FormMachine> speaker4(new FormRcf322A(formParent));
      std::shared_ptr<FormMachine> octlet(new FormOctlet(formParent));
      std::shared_ptr<FormMachine> soundTable3(new FormSimpleSound3(formParent));
      machines.push_back(mic1);
      machines.push_back(mic2);
      machines.push_back(mic3);
      machines.push_back(octlet);
      machines.push_back(speaker1);
      machines.push_back(speaker2);
      machines.push_back(speaker3);
      machines.push_back(speaker4);
      machines.push_back(wallSocket220);
      machines.push_back(soundTable3);
    }
    break;
    case 8:
    {
      //Put a CD on speakers without using a soundtable
      std::shared_ptr<FormMachine> wallSocket220(new FormWallSocket220(formParent));
      std::shared_ptr<FormMachine> speaker1(new FormRcf322A(formParent));
      std::shared_ptr<FormMachine> octlet(new FormOctlet(formParent));
      std::shared_ptr<FormCdPlayer> cdPlayer(new FormCdPlayer(formParent));
      std::shared_ptr<FormTransitionPieceJackMaleTwoCinchFemale> transitionPiece(
        new FormTransitionPieceJackMaleTwoCinchFemale(formParent));
      machines.push_back(octlet);
      machines.push_back(speaker1);
      machines.push_back(wallSocket220);
      machines.push_back(cdPlayer);
      machines.push_back(transitionPiece);
    }
    break;
    case 9:
    {
      //Put a CD on speakers with using a soundtable
      std::shared_ptr<FormMachine> wallSocket220(new FormWallSocket220(formParent));
      std::shared_ptr<FormMachine> speaker1(new FormRcf322A(formParent));
      std::shared_ptr<FormMachine> octlet(new FormOctlet(formParent));
      std::shared_ptr<FormCdPlayer> cdPlayer(new FormCdPlayer(formParent));
      std::shared_ptr<FormMachine> soundTable4(new FormSimpleSound4(formParent));
      machines.push_back(octlet);
      machines.push_back(speaker1);
      machines.push_back(cdPlayer);
      machines.push_back(wallSocket220);
      machines.push_back(soundTable4);
    }
    break;
    case 10:
    {
      //Record a CD on MD play
      std::shared_ptr<FormMachine> wallSocket220(new FormWallSocket220(formParent));
      std::shared_ptr<FormMachine> speaker1(new FormRcf322A(formParent));
      std::shared_ptr<FormMachine> octlet(new FormOctlet(formParent));
      //std::shared_ptr<FormMachine> soundTable4(new FormSimpleSound4(formParent));
      std::shared_ptr<FormMdPlayer> mdPlayer(new FormMdPlayer(formParent));
      std::shared_ptr<FormCdPlayer> cdPlayer(new FormCdPlayer(formParent));
      std::shared_ptr<FormTransitionPieceJackMaleTwoCinchFemale> transitionPiece(
        new FormTransitionPieceJackMaleTwoCinchFemale(formParent));
      machines.push_back(octlet);
      machines.push_back(speaker1);
      machines.push_back(wallSocket220);
      //machines.push_back(soundTable4);
      machines.push_back(mdPlayer);
      machines.push_back(transitionPiece);
      machines.push_back(cdPlayer);
    }
    break;
    case 11:
    {
      //Record a CD and microphone on MD play
      std::shared_ptr<FormMachine> mic1(new FormShureSm58(formParent));
      std::shared_ptr<FormMachine> wallSocket220(new FormWallSocket220(formParent));
      std::shared_ptr<FormMachine> speaker1(new FormRcf322A(formParent));
      std::shared_ptr<FormMachine> octlet(new FormOctlet(formParent));
      std::shared_ptr<FormMachine> soundTable4(new FormSimpleSound4(formParent));
      std::shared_ptr<FormMdPlayer> mdPlayer(new FormMdPlayer(formParent));
      //std::shared_ptr<FormCdPlayer> cdPlayer(new FormCdPlayer(formParent));
      std::shared_ptr<FormTransitionPieceJackMaleTwoCinchFemale> transitionPiece(
        new FormTransitionPieceJackMaleTwoCinchFemale(formParent));
      machines.push_back(wallSocket220);
      machines.push_back(speaker1);
      machines.push_back(octlet);
      machines.push_back(mic1);
      machines.push_back(soundTable4);
      machines.push_back(transitionPiece);
      //machines.push_back(cdPlayer);
      machines.push_back(mdPlayer);
    }
    break;
    case 12:
    {
      //Level 12: Learn to use the crossfader
      std::shared_ptr<FormMachine> dimmerpack(new FormDimblockV3(formParent));
      std::shared_ptr<FormMachine> lighttable(new FormSimpleShine2(formParent));
      std::shared_ptr<FormMachine> wallSocketPower(new FormWallSocketPower(formParent));
      std::shared_ptr<FormMachine> wallSocket220(new FormWallSocket220(formParent));
      std::shared_ptr<FormMachine> par64_1(new FormPar64(formParent));
      std::shared_ptr<FormMachine> par64_2(new FormPar64(formParent));
      std::shared_ptr<FormMachine> par64_3(new FormPar64(formParent));
      std::shared_ptr<FormMachine> par64_4(new FormPar64(formParent));
      std::shared_ptr<FormMachine> par64_5(new FormPar64(formParent));
      machines.push_back(wallSocketPower);
      machines.push_back(dimmerpack);
      machines.push_back(wallSocket220);
      machines.push_back(par64_1);
      machines.push_back(lighttable);
      machines.push_back(par64_2);
      machines.push_back(par64_3);
      machines.push_back(par64_4);
      machines.push_back(par64_5);
    }
    break;
    case 13:
    {
      std::shared_ptr<FormMachine> wallSocket220(new FormWallSocket220(formParent));
      std::shared_ptr<FormMachine> mic(new FormShureSm58(formParent));
      std::shared_ptr<FormMachine> speaker(new FormRcfEvent3000(formParent));
      std::shared_ptr<FormMachine> amplifier(new FormEasyAmp(formParent));
      machines.push_back(mic);
      machines.push_back(speaker);
      machines.push_back(wallSocket220);
      machines.push_back(amplifier);
    }
    break;
    default: //Do nothing
    break;
  }

  return machines;
}
//---------------------------------------------------------------------------
