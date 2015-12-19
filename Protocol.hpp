/******************************************************************************
    Copyright (C) 2002-2015 Argentum Online - Developers

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/

#ifndef PROTOCOL_H
#define PROTOCOL_H
#include <vector>
#include <memory>
#include <string>
#include "vb6compat.h"
#include "enums.h"

extern const std::string SEPARATOR;
void HandleLogged(); //LOGGED
void HandleRemoveDialogs(); //QTDL
void HandleRemoveCharDialog(); //QDL
void HandleNavigateToggle(); //NAVEG
void HandleDisconnect(); //FINOK
void HandleCommerceEnd(); //FINCOMOK
void HandleBankEnd(); //FINBANOK
void HandleCommerceInit(); //INITCOM
void HandleBankInit(); //INITBANCO
void HandleUserCommerceInit(); //INITCOMUSU
void HandleUserCommerceEnd(); //FINCOMUSUOK
void HandleUserOfferConfirm();
void HandleCommerceChat();
void HandleShowBlacksmithForm(); //SFH
void HandleShowCarpenterForm(); //SFC
void HandleUpdateSta(); //ASS
void HandleUpdateMana(); //ASM
void HandleUpdateHP(); //ASH
void HandleUpdateGold(); //ASG
void HandleUpdateBankGold();
void HandleUpdateExp(); //ASE
void HandleChangeMap(); //CM
void HandlePosUpdate(); //PU
void HandleChatOverHead(); //||
void HandleGuildChat(); //|+
void HandleShowMessageBox(); //!!
void HandleUserIndexInServer(); //IU
void HandleUserCharIndexInServer(); //IP
void HandleCharacterCreate(); //CC
void HandleCharacterRemove(); //BP
void HandleCharacterChangeNick();
void HandleCharacterMove(); //MP,+,*and_(); //
void HandleForceCharMove();
void HandleCharacterChange(); //CP
void HandleObjectCreate(); //HO
void HandleObjectDelete(); //BO
void HandleBlockPosition(); //BQ
void HandlePlayMIDI(); //TM
void HandlePlayWave(); //TW
void HandleGuildList(); //GL
void HandleAreaChanged(); //CA
void HandlePauseToggle(); //BKW
void HandleRainToggle(); //LLU
void HandleCreateFX(); //CFX
void HandleUpdateUserStats(); //EST
void HandleWorkRequestTarget(); //T01
void HandleChangeInventorySlot(); //CSI
void HandleChangeBankSlot(); //SBO
void HandleChangeSpellSlot(); //SHS
void HandleAtributes(); //ATR
void HandleBlacksmithWeapons(); //LAH
void HandleBlacksmithArmors(); //LAR
void HandleCarpenterObjects(); //OBR
void HandleRestOK(); //DOK
void HandleErrorMessage(); //ERR
void HandleBlind(); //CEGU
void HandleDumb(); //DUMB
void HandleShowSignal(); //MCAR
void HandleChangeNPCInventorySlot(); //NPCI
void HandleUpdateHungerAndThirst(); //EHYS
void HandleFame(); //FAMA
void HandleConsoleMessage();
void HandleMiniStats(); //MEST
void HandleLevelUp(); //SUNI
void HandleAddForumMessage(); //FMSG
void HandleShowForumForm(); //MFOR
void HandleSetInvisible(); //NOVER
void HandleDiceRoll(); //DADOS
void HandleMeditateToggle(); //MEDOK
void HandleBlindNoMore(); //NSEGUE
void HandleDumbNoMore(); //NESTUP
void HandleSendSkills(); //SKILLS
void HandleTrainerCreatureList(); //LSTCRI
void HandleGuildNews(); //GUILDNE
void HandleOfferDetails(); //PEACEDE&ALLIEDE
void HandleAlianceProposalsList(); //ALLIEPR
void HandlePeaceProposalsList(); //PEACEPR
void HandleCharacterInfo(); //CHRINFO
void HandleGuildLeaderInfo(); //LEADERI
void HandleGuildMemberInfo();
void HandleGuildDetails(); //CLANDET
void HandleShowGuildFundationForm(); //SHOWFUN
void HandleParalizeOK(); //PARADOK
void HandleShowUserRequest(); //PETICIO
void HandleTradeOK(); //TRANSOK
void HandleBankOK(); //BANCOOK
void HandleChangeUserTradeSlot(); //COMUSUINV
void HandleSendNight(); //NOC
void HandlePong();
void HandleUpdateTagAndStatus();

//GMmessages
void HandleSpawnList(); //SPL
void HandleShowSOSForm(); //MSOS
void HandleShowMOTDEditionForm(); //ZMOTD
void HandleShowGMPanelForm(); //ABPANEL
void HandleUserNameList(); //LISTUSU
void HandleShowDenounces();
void HandleRecordList();
void HandleRecordDetails();

void HandleShowGuildAlign();
void HandleShowPartyForm();
void HandleUpdateStrenghtAndDexterity();
void HandleUpdateStrenght();
void HandleUpdateDexterity();
void HandleAddSlots();
void HandleMultiMessage();
void HandleStopWorking();
void HandleCancelOfferItem();
/////////////////////////////////
void ParseUserCommand(std::string);
/////////////////////////////////
void WriteLoginExistingChar(const char*, const char* );
void WriteLoginNewChar(const char*, const char*, char, char, char, short, const char*, char);
void WriteThrowDices();
void WriteWalk(eHeading);
void WriteLeftClick(char, char);
void WriteRightClick(char, char);
void WriteEquipItem(unsigned char);
void WriteUseItem(unsigned char);
void WriteAttack();
void WriteChangeHeading(unsigned char);
void WritePickUp();
void WriteDrop(unsigned char, short);
void WriteWarpChar(std::string, short, unsigned char, unsigned char);
void WriteRequestGuildLeaderInfo();
void WriteCreateNewGuild(std::string, std::string, std::string, std::vector<std::string>);
void WriteGuildRequestMembership(std::string, std::string);
void WriteGuildAcceptNewMember(std::string);
void WriteGuildRejectNewMember(std::string, std::string);
void WriteInvisible();
void WriteTalk(std::string);
void WriteQuit();
//
void HandleIncomingData();
void FlushBuffer();
#endif
