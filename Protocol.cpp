#include <iostream>
#include <sstream>

#include "gamedata.hpp"
#include "inventory.hpp"
#include "Protocol.hpp"
#include "winsock_ao.hpp"
#include "enums.h"
#include "Forms.h"
#include "vb6compat.h"

using namespace std;

void HandleIncomingData()
{
    unsigned char Packet = cGameData::p_cGIn()->incomingData.PeekByte();
    if((int)Packet < 158) std::cout << (int)Packet << std::endl;

    switch (Packet)
    {
        case ServerPacketID::Logged:                  // LOGGED
            HandleLogged();
                break;
        case ServerPacketID::RemoveDialogs:           // QTDL
            HandleRemoveDialogs();
                break;
        case ServerPacketID::RemoveCharDialog:        // QDL
            HandleRemoveCharDialog();
                break;
        case ServerPacketID::NavigateToggle:          // NAVEG
            HandleNavigateToggle();
                break;
        case ServerPacketID::Disconnect:              // FINOK
            HandleDisconnect();
                break;
        case ServerPacketID::CommerceEnd:             // FINCOMOK
            HandleCommerceEnd();
                break;
        case ServerPacketID::CommerceChat:
            HandleCommerceChat();
                break;
        case ServerPacketID::BankEnd:                 // FINBANOK
            HandleBankEnd();
                break;
        case ServerPacketID::CommerceInit:            // INITCOM
            HandleCommerceInit();
                break;
        case ServerPacketID::BankInit:                // INITBANCO
            HandleBankInit();
                break;
        case ServerPacketID::UserCommerceInit:        // INITCOMUSU
            HandleUserCommerceInit();
                break;
        case ServerPacketID::UserCommerceEnd:         // FINCOMUSUOK
            HandleUserCommerceEnd();
                break;
        case ServerPacketID::UserOfferConfirm:
            HandleUserOfferConfirm();
                break;
        case ServerPacketID::ShowBlacksmithForm:      // SFH
            HandleShowBlacksmithForm();
                break;
        case ServerPacketID::ShowCarpenterForm:       // SFC
            HandleShowCarpenterForm();
                break;
        case ServerPacketID::UpdateSta:               // ASS
            HandleUpdateSta();
                break;
        case ServerPacketID::UpdateMana:              // ASM
            HandleUpdateMana();
                break;
        case ServerPacketID::UpdateHP:                // ASH
            HandleUpdateHP();
                break;
        case ServerPacketID::UpdateGold:              // ASG
            HandleUpdateGold();
                break;
        case ServerPacketID::UpdateBankGold:
            HandleUpdateBankGold();
                break;
        case ServerPacketID::UpdateExp:               // ASE
            HandleUpdateExp();
                break;
        case ServerPacketID::ChangeMap:               // CM
            HandleChangeMap();
                break;
        case ServerPacketID::PosUpdate:               // PU
            HandlePosUpdate();
                break;
        case ServerPacketID::ChatOverHead:            // ||
            HandleChatOverHead();
                break;
        case ServerPacketID::ConsoleMsg:              // || - Beware!! its the same as above, but it was properly splitted
            HandleConsoleMessage();
                break;
        case ServerPacketID::GuildChat:               // |+
            HandleGuildChat();
                break;
        case ServerPacketID::ShowMessageBox:          // !!
            HandleShowMessageBox();
                break;
        case ServerPacketID::UserIndexInServer:       // IU
            HandleUserIndexInServer();
                break;
        case ServerPacketID::UserCharIndexInServer:   // IP
            HandleUserCharIndexInServer();
                break;
        case ServerPacketID::CharacterCreate:         // CC
            HandleCharacterCreate();
                break;
        case ServerPacketID::CharacterRemove:         // BP
            HandleCharacterRemove();
                break;
        case ServerPacketID::CharacterChangeNick:
            HandleCharacterChangeNick();
                break;
        case ServerPacketID::CharacterMove:           // MP, +, * and _ //
            HandleCharacterMove();
                break;
        case ServerPacketID::ForceCharMove:
            HandleForceCharMove();
                break;
        case ServerPacketID::CharacterChange:         // CP
            HandleCharacterChange();
                break;
        case ServerPacketID::ObjectCreate:            // HO
            HandleObjectCreate();
                break;
        case ServerPacketID::ObjectDelete:            // BO
            HandleObjectDelete();
                break;
        case ServerPacketID::BlockPosition:           // BQ
            HandleBlockPosition();
                break;
        case ServerPacketID::PlayMidi:                // TM
            HandlePlayMIDI();
                break;
        case ServerPacketID::PlayWave:                // TW
            HandlePlayWave();
                break;
        case ServerPacketID::guildList:               // GL
            HandleGuildList();
                break;
        case ServerPacketID::AreaChanged:             // CA
            HandleAreaChanged();
                break;
        case ServerPacketID::PauseToggle:             // BKW
            HandlePauseToggle();
                break;
        case ServerPacketID::RainToggle:              // LLU
            HandleRainToggle();
                break;
        case ServerPacketID::CreateFX:                // CFX
            HandleCreateFX();
                break;
        case ServerPacketID::UpdateUserStats:         // EST
            HandleUpdateUserStats();
                break;
        case ServerPacketID::WorkRequestTarget:       // T01
            HandleWorkRequestTarget();
                break;
        case ServerPacketID::ChangeInventorySlot:     // CSI
            HandleChangeInventorySlot();
                break;
        case ServerPacketID::ChangeBankSlot:          // SBO
            HandleChangeBankSlot();
                break;
        case ServerPacketID::ChangeSpellSlot:         // SHS
            HandleChangeSpellSlot();
                break;
        case ServerPacketID::Atributes:               // ATR
            HandleAtributes();
                break;
        case ServerPacketID::BlacksmithWeapons:       // LAH
            HandleBlacksmithWeapons();
                break;
        case ServerPacketID::BlacksmithArmors:        // LAR
            HandleBlacksmithArmors();
                break;
        case ServerPacketID::CarpenterObjects:        // OBR
            HandleCarpenterObjects();
                break;
        case ServerPacketID::RestOK:                  // DOK
            HandleRestOK();
                break;
        case ServerPacketID::ErrorMsg:                // ERR
            HandleErrorMessage();
                break;
        case ServerPacketID::Blind:                   // CEGU
            HandleBlind();
                break;
        case ServerPacketID::Dumb:                    // DUMB
            HandleDumb();
                break;
        case ServerPacketID::ShowSignal:              // MCAR
            HandleShowSignal();
                break;
        case ServerPacketID::ChangeNPCInventorySlot:  // NPCI
            HandleChangeNPCInventorySlot();
                break;
        case ServerPacketID::UpdateHungerAndThirst:   // EHYS
            HandleUpdateHungerAndThirst();
                break;
        case ServerPacketID::Fame:                    // FAMA
            HandleFame();
                break;
        case ServerPacketID::MiniStats:               // MEST
            HandleMiniStats();
                break;
        case ServerPacketID::LevelUp:                 // SUNI
            HandleLevelUp();
                break;
        case ServerPacketID::AddForumMsg:             // FMSG
            HandleAddForumMessage();
                break;
        case ServerPacketID::ShowForumForm:           // MFOR
            HandleShowForumForm();
                break;
        case ServerPacketID::SetInvisible:            // NOVER
            HandleSetInvisible();
                break;
        case ServerPacketID::DiceRoll:                // DADOS
            HandleDiceRoll();
                break;
        case ServerPacketID::MeditateToggle:          // MEDOK
            HandleMeditateToggle();
                break;
        case ServerPacketID::BlindNoMore:             // NSEGUE
            HandleBlindNoMore();
                break;
        case ServerPacketID::DumbNoMore:              // NESTUP
            HandleDumbNoMore();
                break;
        case ServerPacketID::SendSkills:              // SKILLS
            HandleSendSkills();
                break;
        case ServerPacketID::TrainerCreatureList:     // LSTCRI
            HandleTrainerCreatureList();
                break;
        case ServerPacketID::guildNews:               // GUILDNE
            HandleGuildNews();
                break;
        case ServerPacketID::OfferDetails:            // PEACEDE and ALLIEDE
            HandleOfferDetails();
                break;
        case ServerPacketID::AlianceProposalsList:    // ALLIEPR
            HandleAlianceProposalsList();
                break;
        case ServerPacketID::PeaceProposalsList:      // PEACEPR
            HandlePeaceProposalsList();
                break;
        case ServerPacketID::CharacterInfo:           // CHRINFO
            HandleCharacterInfo();
                break;
        case ServerPacketID::GuildLeaderInfo:         // LEADERI
            HandleGuildLeaderInfo();
                break;
        case ServerPacketID::GuildDetails:            // CLANDET
            HandleGuildDetails();
                break;
        case ServerPacketID::ShowGuildFundationForm:  // SHOWFUN
            HandleShowGuildFundationForm();
                break;
        case ServerPacketID::ParalizeOK:              // PARADOK
            HandleParalizeOK();
                break;
        case ServerPacketID::ShowUserRequest:         // PETICIO
            HandleShowUserRequest();
                break;
        case ServerPacketID::TradeOK:                 // TRANSOK
            HandleTradeOK();
                break;
        case ServerPacketID::BankOK:                  // BANCOOK
            HandleBankOK();
                break;
        case ServerPacketID::ChangeUserTradeSlot:     // COMUSUINV
            HandleChangeUserTradeSlot();
                break;
        case ServerPacketID::SendNight:               // NOC
            HandleSendNight();
                break;
        case ServerPacketID::Pong:
            HandlePong();
                break;
        case ServerPacketID::UpdateTagAndStatus:
            HandleUpdateTagAndStatus();
                break;
        case ServerPacketID::GuildMemberInfo:
            HandleGuildMemberInfo();
                break;
        //*******************
        //GM messages
        //*******************
        case ServerPacketID::SpawnList:               // SPL
            HandleSpawnList();
                break;
        case ServerPacketID::ShowSOSForm:             // RSOS and MSOS
            HandleShowSOSForm();
                break;
        case ServerPacketID::ShowDenounces:
            HandleShowDenounces();
                break;
        case ServerPacketID::RecordDetails:
            HandleRecordDetails();
                break;
        case ServerPacketID::RecordList:
            HandleRecordList();
                break;
        case ServerPacketID::ShowMOTDEditionForm:     // ZMOTD
            HandleShowMOTDEditionForm();
                break;
        case ServerPacketID::ShowGMPanelForm:         // ABPANEL
            HandleShowGMPanelForm();
                break;
        case ServerPacketID::UserNameList:            // LISTUSU
            HandleUserNameList();
                break;
        case ServerPacketID::ShowGuildAlign:
            HandleShowGuildAlign();
                break;
        case ServerPacketID::ShowPartyForm:
            HandleShowPartyForm();
                break;
        case ServerPacketID::UpdateStrenghtAndDexterity:
            HandleUpdateStrenghtAndDexterity();
                break;
        case ServerPacketID::UpdateStrenght:
            HandleUpdateStrenght();
                break;
        case ServerPacketID::UpdateDexterity:
            HandleUpdateDexterity();
                break;
        case ServerPacketID::AddSlots:
            HandleAddSlots();
                break;
        case ServerPacketID::MultiMessage:
            HandleMultiMessage();
                break;
        case ServerPacketID::StopWorking:
            HandleStopWorking();
                break;
        case ServerPacketID::CancelOfferItem:
            HandleCancelOfferItem();
                break;
    }

    if (cGameData::p_cGIn()->incomingData.length() > 0)
    {
        HandleIncomingData();
    }
}

void HandleLogged()
{
    cGameData* _P = cGameData::p_cGIn();
    _P->incomingData.ReadByte();
    unsigned char UserClase = _P->incomingData.ReadByte();
	_P->Connected = true;
	FCreateCharacter_Visible(false);
	FConnect_Visible(false);
	FMain_Visible(true);
}

void HandleRemoveDialogs()
{
    cGameData* _P = cGameData::p_cGIn();
    _P->incomingData.ReadByte();
}

void HandleRemoveCharDialog()
{
    cGameData* _P = cGameData::p_cGIn();
    _P->incomingData.ReadByte();
    _P->incomingData.ReadInteger(); //Call Dialogos.RemoveDialog(incomingData.ReadInteger())
}

void HandleGuildChat()
{
    clsByteQueue* buff = &cGameData::p_cGIn()->incomingData;

    buff->ReadByte();
    cout << "HandleGuildChat: " << buff->ReadUnicodeString() << endl;
}

void HandleUserOfferConfirm()
{
    cGameData* _P = cGameData::p_cGIn();
    _P->incomingData.ReadByte();

    cout << "USUARIO ha confirmado su oferta!!!" << endl;
}

void HandleUpdateSta()
{
    cGameData* _P = cGameData::p_cGIn();
    _P->incomingData.ReadByte();

    _P->UserMinSTA = _P->incomingData.ReadInteger();
}

void HandleUpdateMana()
{
    cGameData* _P = cGameData::p_cGIn();
    _P->incomingData.ReadByte();

    _P->UserMinMAN = _P->incomingData.ReadInteger();
}

void HandleUpdateHP()
{
    cGameData* _P = cGameData::p_cGIn();
    _P->incomingData.ReadByte();

    _P->UserMinHP = _P->incomingData.ReadInteger();
}

void HandleUpdateGold()
{
    cGameData* _P = cGameData::p_cGIn();
    _P->incomingData.ReadByte();

    _P->UserGLD = _P->incomingData.ReadInteger();
}

void HandleChangeMap()
{
    cGameData* _P = cGameData::p_cGIn();
    _P->incomingData.ReadByte();
    _P->UserMap = _P->incomingData.ReadInteger();
    _P->incomingData.ReadInteger();

    //condiciones:

    _P->LoadMap(_P->UserMap);
}

void HandleUserIndexInServer()
{
    cGameData* _P = cGameData::p_cGIn();
    _P->incomingData.ReadByte();
    short UserIndex = _P->incomingData.ReadInteger();
}

void HandleUserCharIndexInServer()
{
    cGameData* _P = cGameData::p_cGIn();
    _P->incomingData.ReadByte();

    _P->UserCharIndex = _P->incomingData.ReadInteger();
    _P->UserPos.x = _P->charlist[_P->UserCharIndex].Pos.x;
    _P->UserPos.y = _P->charlist[_P->UserCharIndex].Pos.y;

    _P->Update_bTecho(_P->UserPos.x, _P->UserPos.y);
}

void HandleErrorMessage()
{
    clsByteQueue* buff = &cGameData::p_cGIn()->incomingData;
    buff->ReadByte();
    cout << "HandleErrorMessage: " << buff->ReadUnicodeString() << endl;
}

void HandleConsoleMessage()
{
    clsByteQueue* buff = &cGameData::p_cGIn()->incomingData;
    buff->ReadByte();

	const char* text = buff->ReadUnicodeString().c_str();
	int fontindex = buff->ReadByte();

	FMain_AddItem_Console(text, cGameData::p_cGIn()->FontTypes[fontindex].color, cGameData::p_cGIn()->FontTypes[fontindex].bold, cGameData::p_cGIn()->FontTypes[fontindex].italic);
    //char fontindex;
}

void HandleCharacterChange()
{
    cGameData* _P = cGameData::p_cGIn();
    _P->incomingData.ReadByte();

    short CharIndex = _P->incomingData.ReadInteger();
    short tempint = _P->incomingData.ReadInteger();

    if ((tempint < UBound(_P->BodyData)) || (tempint < 0))
    {
        _P->charlist[CharIndex].Body = _P->BodyData[0];
        _P->charlist[CharIndex].iBody = 0;
    }
    else
    {
        _P->charlist[CharIndex].Body = _P->BodyData[tempint];
        _P->charlist[CharIndex].iBody = tempint;
    }

    short headIndex = _P->incomingData.ReadInteger();
    if ((headIndex < UBound(_P->HeadData)) || (headIndex < 0))
    {
        _P->charlist[CharIndex].Head = _P->HeadData[0];
        _P->charlist[CharIndex].iHead = 0;
    }
    else
    {
        _P->charlist[CharIndex].Head = _P->HeadData[headIndex];
        _P->charlist[CharIndex].iHead = headIndex;
    }

    if (headIndex == CASPER_HEAD)
    {
        _P->charlist[CharIndex].dead = true;
    }
    else
    {
        _P->charlist[CharIndex].dead = false;
    }

    char bHeading = _P->incomingData.ReadByte();
    eHeading nHeading = static_cast<eHeading>(bHeading);

    _P->charlist[CharIndex].Heading = nHeading;
    //
    tempint = _P->incomingData.ReadInteger();
    if (tempint != 0) _P->charlist[CharIndex].Weapon = _P->WeaponData[tempint];
	if (tempint <= 0 || tempint == 2) _P->charlist[CharIndex].Weapon = _P->WeaponData[0];

    tempint = _P->incomingData.ReadInteger();
    if (tempint != 0) _P->charlist[CharIndex].Shield = _P->ShieldData[tempint];
	if (tempint <= 0 || tempint == 2) _P->charlist[CharIndex].Shield = _P->ShieldData[0];

    tempint = _P->incomingData.ReadInteger();
    if (tempint != 0) _P->charlist[CharIndex].Helmet = _P->HelmetsData[tempint];
	if (tempint <= 0 || tempint == 2) _P->charlist[CharIndex].Helmet = _P->HelmetsData[0];

    short fX = _P->incomingData.ReadInteger();
    short Loops = _P->incomingData.ReadInteger();

    _P->SetCharacterFX(CharIndex, fX, Loops);
    _P->RefreshAllChars();
}

void HandleObjectCreate()
{
    cGameData* _P = cGameData::p_cGIn();
    _P->incomingData.ReadByte();

    short X = _P->incomingData.ReadInteger();
    short Y = _P->incomingData.ReadInteger();
    short grhIndex = _P->incomingData.ReadInteger();

    _P->MapData[X][Y].objgrh.grhIndex = grhIndex;
    _P->InitGrh(_P->MapData[X][Y].objgrh, grhIndex, false);
}

void HandlePlayMIDI()
{
    cGameData* _P = cGameData::p_cGIn();
    _P->incomingData.ReadByte();

    short currentMidi = _P->incomingData.ReadInteger();
    short Loops = _P->incomingData.ReadInteger();
	
	std::ostringstream ss;
	ss << currentMidi;

    _P->Audio.PlayMIDI("resources/MIDI/" + ss.str() + ".ogg");
}

void HandleGuildList()
{
	clsByteQueue* buff = &cGameData::p_cGIn()->incomingData;
	buff->ReadByte();
	cGameData::p_cGIn()->GuildNames = vb6::split(buff->ReadUnicodeString(), L'\0');
	FMain_Reload_GuildList();
	FMain_GuildList_Visible(true);
}

void HandlePlayWave()
{
    cGameData* _P = cGameData::p_cGIn();
    _P->incomingData.ReadByte();

    short wave = _P->incomingData.ReadInteger();
    short srcX = _P->incomingData.ReadInteger();
    short srcY = _P->incomingData.ReadInteger();

    stringstream numberwave;
    numberwave << wave;

    _P->Audio.PlayWav("resources/wav/" + numberwave.str() + ".wav");
}

void HandleBlockPosition()
{
    cGameData* _P = cGameData::p_cGIn();
    _P->incomingData.ReadByte();

    short X = _P->incomingData.ReadInteger();
    short Y = _P->incomingData.ReadInteger();

    bool is = _P->incomingData.ReadBoolean();
	
	_P->MapData[X][Y].blocked = 0;
	if (is) _P->MapData[X][Y].blocked = 1;
}

void HandleRainToggle()
{
    cGameData* _P = cGameData::p_cGIn();
    _P->incomingData.ReadByte();

    _P->Update_bTecho(_P->UserPos.x, _P->UserPos.y);
    //hacer todo el raintoggle
}

void HandleCreateFX()
{
    cGameData* _P = cGameData::p_cGIn();
    _P->incomingData.ReadByte();

    short CharIndex = _P->incomingData.ReadInteger();
    short fX = _P->incomingData.ReadInteger();
    short Loops = _P->incomingData.ReadInteger();

    _P->SetCharacterFX(CharIndex, fX, Loops);
}

void HandleForceCharMove()
{
    cGameData* _P = cGameData::p_cGIn();
    _P->incomingData.ReadByte();

    unsigned char Direction = _P->incomingData.ReadByte();
    _P->MoveCharbyHead(_P->UserCharIndex, static_cast<eHeading>(Direction));
    _P->MoveScreen(static_cast<eHeading>(Direction));

    _P->RefreshAllChars();
}

void HandleUpdateUserStats()
{
    cGameData* _P = cGameData::p_cGIn();
    _P->incomingData.ReadByte();

	_P->UserMaxHP = _P->incomingData.ReadInteger();
	_P->UserMinHP = _P->incomingData.ReadInteger();
	_P->UserMaxMAN = _P->incomingData.ReadInteger();
	_P->UserMinMAN = _P->incomingData.ReadInteger();
	_P->UserMaxSTA = _P->incomingData.ReadInteger();
	_P->UserMinSTA = _P->incomingData.ReadInteger();
	_P->UserGLD = _P->incomingData.ReadLong();
	_P->UserLvl = _P->incomingData.ReadByte();
	_P->UserPasarNivel = _P->incomingData.ReadLong();
	_P->UserExp = _P->incomingData.ReadLong();

	float UserPercentage = (float)_P->UserExp / (float)_P->UserPasarNivel;
	FMain_setExpBar(UserPercentage);
}

void HandleChangeInventorySlot()
{
    clsByteQueue* buff = &cGameData::p_cGIn()->incomingData;
    buff->ReadByte();

    unsigned char slot = buff->ReadByte();
    short OBJIndex = buff->ReadInteger();

    string name = buff->ReadUnicodeString();
    short amount = buff->ReadInteger();
    bool equipped = buff->ReadBoolean();
    short grhIndex = buff->ReadInteger();
    unsigned char objtype = buff->ReadByte();
    short maxhit = buff->ReadInteger();
    short minhit = buff->ReadInteger();
    short maxdef = buff->ReadInteger();
    short mindef = buff->ReadInteger();
    float value = buff->ReadSingle();

    cGameData::p_cGIn()->CharInventory.SetItem(slot, OBJIndex, amount, equipped, grhIndex, objtype, maxhit, minhit, maxdef, mindef, value, name);
}

void HandleUpdateHungerAndThirst()
{
    cGameData* _P = cGameData::p_cGIn();
    _P->incomingData.ReadByte();

    cGameData::p_cGIn()->UserMaxAGU = _P->incomingData.ReadByte();
    cGameData::p_cGIn()->UserMinAGU = _P->incomingData.ReadByte();
    cGameData::p_cGIn()->UserMaxHAM = _P->incomingData.ReadByte();
    cGameData::p_cGIn()->UserMinHAM = _P->incomingData.ReadByte();
}

void HandlePosUpdate()
{
    cGameData* _P = cGameData::p_cGIn();
    _P->incomingData.ReadByte();

    if (_P->MapData[_P->UserPos.x][_P->UserPos.y].charindex = _P->UserCharIndex)
    {
        _P->MapData[_P->UserPos.x][_P->UserPos.y].charindex = 0;
    }

    _P->UserPos.x = _P->incomingData.ReadByte();
    _P->UserPos.y = _P->incomingData.ReadByte();

    _P->MapData[_P->UserPos.x][_P->UserPos.y].charindex = _P->UserCharIndex;
    _P->charlist[_P->UserCharIndex].Pos = _P->UserPos;

    _P->Update_bTecho(_P->UserPos.x, _P->UserPos.y);
}

void HandleAreaChanged()
{
    cGameData* _P = cGameData::p_cGIn();
    _P->incomingData.ReadByte();
    short X = _P->incomingData.ReadInteger();
    short Y = _P->incomingData.ReadInteger();
    _P->ChangeArea(X, Y);
}

void HandleCharacterChangeNick()
{
	cGameData* _P = cGameData::p_cGIn();
	_P->incomingData.ReadByte();
	short CharIndex = _P->incomingData.ReadInteger();
	_P->charlist[CharIndex].name = _P->incomingData.ReadUnicodeString();
}

void HandleCharacterMove()
{
    cGameData* _P = cGameData::p_cGIn();
    _P->incomingData.ReadByte();
    short CharIndex = _P->incomingData.ReadInteger();
    short X = _P->incomingData.ReadInteger();
    short Y = _P->incomingData.ReadInteger();
    if ((_P->charlist[CharIndex].FxIndex >= 40) && (_P->charlist[CharIndex].FxIndex <= 49))
    {
        _P->charlist[CharIndex].FxIndex = 0;
    }

    if ((_P->charlist[CharIndex].priv != 1) && (_P->charlist[CharIndex].priv != 2)
         && (_P->charlist[CharIndex].priv != 3) && (_P->charlist[CharIndex].priv != 5)
         && (_P->charlist[CharIndex].priv != 25))
    {
        _P->DoPasosFx(CharIndex);
    }

    _P->MoveCharbyPos(CharIndex, X, Y);
    _P->RefreshAllChars();
}

void HandleCharacterCreate()
{
    clsByteQueue* buff = &cGameData::p_cGIn()->incomingData;
    buff->ReadByte();

    short CharIndex = buff->ReadInteger();
    short Body = buff->ReadInteger();
    short Head = buff->ReadInteger();

    char Heading = buff->ReadByte();
    eHeading nHeading = static_cast<eHeading>(Heading);

    short X = buff->ReadInteger();
    short Y = buff->ReadInteger();

    short weapon = buff->ReadInteger();
    short shield = buff->ReadInteger();
    short helmet = buff->ReadInteger();

    /*SetCharacterFX()*/
    short fX = buff->ReadInteger();
    short Loops = buff->ReadInteger();

    cGameData::p_cGIn()->SetCharacterFX(CharIndex, fX, Loops);
    /*SetCharacterFX()*/

    string name = buff->ReadUnicodeString();

    char NickColor = buff->ReadByte();

    cGameData::p_cGIn()->charlist[CharIndex].criminal = 0;
    if ((NickColor & 1) != 0) cGameData::p_cGIn()->charlist[CharIndex].criminal = 1;

    cGameData::p_cGIn()->charlist[CharIndex].attackable = cGameData::p_cGIn()->charlist[CharIndex].criminal;

    char privs = buff->ReadByte();
    if (privs != 0)
    {
        cGameData::p_cGIn()->charlist[CharIndex].priv = privs;
    }

    cGameData::p_cGIn()->MakeChar(CharIndex, name, Body, Head, nHeading, X, Y, weapon, shield, helmet);
    cGameData::p_cGIn()->RefreshAllChars();
}

void HandleCharacterRemove()
{
    cGameData* _P = cGameData::p_cGIn();
    _P->incomingData.ReadByte();

    short CharIndex = _P->incomingData.ReadInteger();

    _P->EraseChar(CharIndex);
    _P->RefreshAllChars();
}

void HandleLevelUp()
{
    cGameData* _P = cGameData::p_cGIn();
    _P->incomingData.ReadByte();
    _P->SkillPoints += _P->incomingData.ReadInteger();
}

void HandleSendSkills()
{
    cGameData* _P = cGameData::p_cGIn();
    _P->incomingData.ReadByte();

    _P->UserSkills = new short[NUMSKILLS + 1];
    _P->PorcentajeSkills = new short[NUMSKILLS + 1];

    for(short i = 1; i <= NUMSKILLS; ++i)
    {
        _P->UserSkills[i] = _P->incomingData.ReadByte();
        _P->PorcentajeSkills[i] = _P->incomingData.ReadByte();
    }

    _P->Geted_Skills = true;
}

void HandleShowForumForm()
{
    cGameData* _P = cGameData::p_cGIn();
    _P->incomingData.ReadByte();
    _P->incomingData.ReadByte(); //FALTA TERMINAR
}

void HandleDiceRoll()
{
    cGameData* _P = cGameData::p_cGIn();
	_P->incomingData.ReadByte();
	FCreateCharacter_Visible(true);
	FMain_Visible(false);
	FConnect_Visible(false);
	FCreateCharacter_setAttributes(_P->incomingData.ReadByte(), _P->incomingData.ReadByte(), _P->incomingData.ReadByte(), _P->incomingData.ReadByte(), _P->incomingData.ReadByte());
	_P->UserPos.x = 53;
	_P->UserPos.y = 49;
	_P->LoadMap(140);
}

void HandleUpdateStrenght()
{
    cGameData* _P = cGameData::p_cGIn();
    _P->incomingData.ReadByte();
    _P->UserStrength = _P->incomingData.ReadByte();
}

void HandleUpdateStrenghtAndDexterity()
{
    cGameData* _P = cGameData::p_cGIn();
    _P->incomingData.ReadByte();
    _P->UserStrength = _P->incomingData.ReadByte();
    _P->UserDexterity = _P->incomingData.ReadByte();
}

void HandleMultiMessage()
{
    cGameData* _P = cGameData::p_cGIn();
    _P->incomingData.ReadByte();

    switch (_P->incomingData.ReadByte())
    {
        case eMessages::eMessages_DontSeeAnything:
            cout << "COMBATE>> " << MENSAJE_NO_VES_NADA_INTERESANTE << endl;
                break;
        case eMessages::eMessages_NPCSwing:
            cout << "COMBATE>> " << MENSAJE_NO_VES_NADA_INTERESANTE << endl;
                break;
        case eMessages::eMessages_NPCKillUser:
            cout << "COMBATE>> " << MENSAJE_NO_VES_NADA_INTERESANTE << endl;
                break;
        case eMessages::eMessages_BlockedWithShieldUser:
            cout << "COMBATE>> " << MENSAJE_NO_VES_NADA_INTERESANTE << endl;
                break;
        case eMessages::eMessages_BlockedWithShieldother:
            cout << "COMBATE>> " << MENSAJE_NO_VES_NADA_INTERESANTE << endl;
                break;
        case eMessages::eMessages_UserSwing:
            cout << "COMBATE>> " << MENSAJE_NO_VES_NADA_INTERESANTE << endl;
                break;
        case eMessages::eMessages_SafeModeOn:
            cout << "COMBATE>> " << MENSAJE_NO_VES_NADA_INTERESANTE << endl;
                break;
        case eMessages::eMessages_SafeModeOff:
            cout << "COMBATE>> " << MENSAJE_NO_VES_NADA_INTERESANTE << endl;
                break;
        case eMessages::eMessages_ResuscitationSafeOff:
            cout << "COMBATE>> " << MENSAJE_NO_VES_NADA_INTERESANTE << endl;
                break;
        case eMessages::eMessages_ResuscitationSafeOn:
            cout << "COMBATE>> " << MENSAJE_NO_VES_NADA_INTERESANTE << endl;
                break;
        case eMessages::eMessages_NobilityLost:
            cout << "COMBATE>> " << MENSAJE_NO_VES_NADA_INTERESANTE << endl;
                break;
        case eMessages::eMessages_CantUseWhileMeditating:
            cout << "COMBATE>> " << MENSAJE_NO_VES_NADA_INTERESANTE << endl;
                break;

        case eMessages::eMessages_NPCHitUser:
            switch (_P->incomingData.ReadByte())
            {
                //
            }
    }
}

void HandleNavigateToggle()
{
    cGameData::p_cGIn()->incomingData.ReadByte();
    cGameData::p_cGIn()->UserNavegando = !cGameData::p_cGIn()->UserNavegando;
}

void HandleDisconnect()
{
	cGameData* _P = cGameData::p_cGIn();
	_P->incomingData.ReadByte();
	//_P->charlist[_P->UserCharIndex].Pos.x = 50;
	//_P->charlist[_P->UserCharIndex].Pos.y = 50;
	_P->Connected = false;

	FMain_Visible(false);
	FConnect_Visible(true);
	//cWinsock::p_cGIn()->listening = false;
}

void HandleCommerceEnd()
{

}

void HandleBankEnd()
{

}

void HandleCommerceInit()
{
    clsByteQueue* buff = &cGameData::p_cGIn()->incomingData;
    buff->ReadByte(); //FALTA TERMINAR
}

void HandleBankInit()
{

}

void HandleUserCommerceInit()
{

}

void HandleUserCommerceEnd()
{

}

void HandleCommerceChat()
{

}

void HandleShowBlacksmithForm()
{

}

void HandleShowCarpenterForm()
{

}

void HandleUpdateBankGold()
{

}

void HandleUpdateExp()
{
    cGameData* _P = cGameData::p_cGIn();
    _P->incomingData.ReadByte();
    _P->UserExp = _P->incomingData.ReadLong();

	float UserPercentage = (float)_P->UserExp / (float)_P->UserPasarNivel;
	FMain_setExpBar(UserPercentage);
}

void HandleChatOverHead()
{
    clsByteQueue* buff = &cGameData::p_cGIn()->incomingData;
    buff->ReadByte();

    string chat = buff->ReadUnicodeString();
    short charindex = buff->ReadInteger();

    unsigned char r = buff->ReadByte();
    unsigned char g = buff->ReadByte();
    unsigned char b = buff->ReadByte();

    cGameData::p_cGIn()->Char_Dialog_Set(charindex, chat, -1, 10, 1);
}

void HandleShowMessageBox()
{

}

void HandleObjectDelete()
{
    cGameData* _P = cGameData::p_cGIn();
    _P->incomingData.ReadByte();

    short X = _P->incomingData.ReadInteger();
    short Y = _P->incomingData.ReadInteger();

    _P->MapData[X][Y].objgrh.grhIndex = 0;
}

void HandlePauseToggle()
{

}

void HandleWorkRequestTarget()
{

}

void HandleChangeBankSlot()
{

}

void HandleChangeSpellSlot()
{

}

void HandleAtributes()
{

}

void HandleBlacksmithWeapons()
{

}

void HandleBlacksmithArmors()
{

}

void HandleCarpenterObjects()
{

}

void HandleRestOK()
{
    cGameData::p_cGIn()->incomingData.ReadByte();
    cGameData::p_cGIn()->UserDescansar = !cGameData::p_cGIn()->UserDescansar;
}

void HandleBlind()
{
    cGameData::p_cGIn()->incomingData.ReadByte();
    //UserCiego = true;
}

void HandleDumb()
{
    cGameData::p_cGIn()->incomingData.ReadByte();
    //UserEstupido = true;
}

void HandleShowSignal()
{

}

void HandleChangeNPCInventorySlot()
{
    clsByteQueue* buff = &cGameData::p_cGIn()->incomingData;
    buff->ReadByte();

    unsigned char index = buff->ReadByte();
    std::string name = buff->ReadUnicodeString();
    short amount = buff->ReadInteger();
    float value = buff->ReadSingle();
    short grhIndex = buff->ReadInteger();
    short objindex = buff->ReadInteger();
    unsigned char objtype = buff->ReadByte();
    short maxhit = buff->ReadInteger();
    short minhit = buff->ReadInteger();
    short maxdef = buff->ReadInteger();
    short mindef = buff->ReadInteger();

    cGameData::p_cGIn()->NPCInventory.SetItem(index, objindex, amount, false, grhIndex, objtype, maxhit, minhit, maxdef, mindef, value, name);
    cGameData::p_cGIn()->NPCInventory.visible = true;
}

void HandleFame()
{

}

void HandleMiniStats()
{

}

void HandleAddForumMessage()
{

}

void HandleSetInvisible()
{
    cGameData* GameData = cGameData::p_cGIn();
    GameData->incomingData.ReadByte();
    short CharIndex = GameData->incomingData.ReadInteger();
    GameData->charlist[CharIndex].invisible = GameData->incomingData.ReadBoolean();
}

void HandleMeditateToggle()
{

}

void HandleBlindNoMore()
{

}

void HandleDumbNoMore()
{

}

void HandleTrainerCreatureList()
{

}
void HandleGuildNews()
{
	clsByteQueue* buff = &cGameData::p_cGIn()->incomingData;
	buff->ReadByte();
	FMain_GuildNews_setText(buff->ReadUnicodeString().c_str());
	std::vector<std::string>guildList = vb6::split(buff->ReadUnicodeString(), L'\0');
	//for (int i = 0; blabla){}
	guildList = vb6::split(buff->ReadUnicodeString(), L'\0');
}

void HandleOfferDetails()
{

}

 //PEACEDE&ALLIEDE
void HandleAlianceProposalsList()
{

}

 //ALLIEPR
void HandlePeaceProposalsList()
{

}

 //PEACEPR
void HandleCharacterInfo()
{

}

 //CHRINFO
void HandleGuildLeaderInfo()
{
	clsByteQueue* buff = &cGameData::p_cGIn()->incomingData;
	cGameData* GameData = cGameData::p_cGIn();

	buff->ReadByte();
	GameData->GuildNames = vb6::split(buff->ReadUnicodeString(), L'\0');
	GameData->GuildMembers = vb6::split(buff->ReadUnicodeString(), L'\0');
	std::cout << "Quest guild news: " << buff->ReadUnicodeString() << std::endl;
	GameData->GuildAspirantes = vb6::split(buff->ReadUnicodeString(), L'\0');
	FMain_Reload_GuildList();
	FMain_Reload_GuildMember();
	FMain_Reload_GuildAspirantes();
	FMain_GuildLeader_Visible(true, true);
}

 //LEADERI
void HandleGuildMemberInfo()
{
	clsByteQueue* buff = &cGameData::p_cGIn()->incomingData;
	cGameData* GameData = cGameData::p_cGIn();

	buff->ReadByte();
	GameData->GuildNames = vb6::split(buff->ReadUnicodeString(), L'\0');
	GameData->GuildMembers = vb6::split(buff->ReadUnicodeString(), L'\0');
	FMain_Reload_GuildList();
	FMain_Reload_GuildMember();
	FMain_GuildLeader_Visible(true, false);
}


void HandleGuildDetails()
{

}

 //CLANDET
void HandleShowGuildFundationForm()
{

}

 //SHOWFUN
void HandleParalizeOK()
{

}

 //PARADOK
void HandleShowUserRequest()
{

}

 //PETICIO
void HandleTradeOK()
{

}

 //TRANSOK
void HandleBankOK()
{

}

 //BANCOOK
void HandleChangeUserTradeSlot()
{

}

 //COMUSUINV
void HandleSendNight()
{

}

 //NOC
void HandlePong()
{

}


void HandleUpdateTagAndStatus()
{

}



//GMmessages
void HandleSpawnList()
{

}

 //SPL
void HandleShowSOSForm()
{

}

 //MSOS
void HandleShowMOTDEditionForm()
{

}

 //ZMOTD
void HandleShowGMPanelForm()
{

}

 //ABPANEL
void HandleUserNameList()
{

}

 //LISTUSU
void HandleShowDenounces()
{

}


void HandleRecordList()
{

}


void HandleRecordDetails()
{

}



void HandleShowGuildAlign()
{

}


void HandleShowPartyForm()
{

}


void HandleUpdateDexterity()
{

}


void HandleAddSlots()
{

}

void HandleStopWorking()
{

}


void HandleCancelOfferItem()
{

}

void ParseUserCommand(std::string RawCommand)
{
	WriteTalk(RawCommand);
}

void WriteThrowDices()
{
    cGameData* _P = cGameData::p_cGIn();
    _P->outgoingData.WriteByte(ClientPacketID::ClientPacketID_ThrowDices);
}

void WriteLoginExistingChar(const char* name, const char* password)
{
    cGameData* _P = cGameData::p_cGIn();

    _P->outgoingData.WriteByte(ClientPacketID::ClientPacketID_LoginExistingChar);
    _P->outgoingData.WriteUnicodeString(name);
    _P->outgoingData.WriteUnicodeString(password);
    _P->outgoingData.WriteByte(0);
    _P->outgoingData.WriteByte(13);
    _P->outgoingData.WriteByte(0);
}

void WriteLoginNewChar(const char* username, const char* userpassword, char userraza,
						char usergenero, char userclase, short userhead, const char* useremail, char userhogar)
{
    cGameData* _P = cGameData::p_cGIn();
    _P->outgoingData.WriteByte(ClientPacketID::ClientPacketID_LoginNewChar);
    _P->outgoingData.WriteUnicodeString(username);
    _P->outgoingData.WriteUnicodeString(userpassword);
    _P->outgoingData.WriteByte(0);
    _P->outgoingData.WriteByte(13);
    _P->outgoingData.WriteByte(0);
    _P->outgoingData.WriteByte(userraza); //eRaza::Humano
    _P->outgoingData.WriteByte(usergenero); //eGenero::eGenero_Hombre
    _P->outgoingData.WriteByte(userclase); //eClass::eClass_Paladin
    _P->outgoingData.WriteInteger(userhead);
    _P->outgoingData.WriteUnicodeString(useremail);
    _P->outgoingData.WriteByte(userhogar); //eCiudad::eCiudad_cUllathorpe
}

void WriteWalk(eHeading Heading)
{
    cGameData* _P = cGameData::p_cGIn();
    _P->outgoingData.WriteByte(ClientPacketID::ClientPacketID_Walk);
    _P->outgoingData.WriteByte(Heading);
}

void WriteLeftClick(char X, char Y)
{
    cGameData* _P = cGameData::p_cGIn();
    _P->outgoingData.WriteByte(ClientPacketID::ClientPacketID_LeftClick);
    _P->outgoingData.WriteByte(X);
    _P->outgoingData.WriteByte(Y);
}

void WriteRightClick(char X, char Y)
{
    cGameData* _P = cGameData::p_cGIn();
    _P->outgoingData.WriteByte(ClientPacketID::ClientPacketID_RightClick);
    _P->outgoingData.WriteByte(X);
    _P->outgoingData.WriteByte(Y);
}

void WriteEquipItem(unsigned char slot)
{
    cGameData* _P = cGameData::p_cGIn();
    _P->outgoingData.WriteByte(ClientPacketID::ClientPacketID_EquipItem);
    _P->outgoingData.WriteByte(slot);
}

void WriteUseItem(unsigned char slot)
{
    cGameData* _P = cGameData::p_cGIn();
    _P->outgoingData.WriteByte(ClientPacketID::ClientPacketID_UseItem);
    _P->outgoingData.WriteByte(slot);
}

void WriteAttack()
{
    cGameData::p_cGIn()->outgoingData.WriteByte(ClientPacketID::ClientPacketID_Attack);
}

void WriteChangeHeading(unsigned char Heading)
{
    cGameData::p_cGIn()->outgoingData.WriteByte(ClientPacketID::ClientPacketID_ChangeHeading);
    cGameData::p_cGIn()->outgoingData.WriteByte(Heading);
}

void WritePickUp()
{
    cGameData::p_cGIn()->outgoingData.WriteByte(ClientPacketID::ClientPacketID_PickUp);
}

void WriteDrop(unsigned char slot, short amount)
{
    cGameData::p_cGIn()->outgoingData.WriteByte(ClientPacketID::ClientPacketID_Drop);
    cGameData::p_cGIn()->outgoingData.WriteByte(slot);
    cGameData::p_cGIn()->outgoingData.WriteInteger(amount);
}

void WriteWarpChar(std::string UserName, short nmap, unsigned char x, unsigned char y)
{
    cGameData::p_cGIn()->outgoingData.WriteByte(ClientPacketID::ClientPacketID_GMCommands);
    cGameData::p_cGIn()->outgoingData.WriteByte(eGMCommands::eGMCommands_WarpChar);
    cGameData::p_cGIn()->outgoingData.WriteUnicodeString(UserName);
    cGameData::p_cGIn()->outgoingData.WriteInteger(nmap);
    cGameData::p_cGIn()->outgoingData.WriteByte(x);
    cGameData::p_cGIn()->outgoingData.WriteByte(y);
}

void WriteCreateNewGuild(std::string desc, std::string name, std::string url, std::vector<std::string> codex)
{
	cGameData* _P = cGameData::p_cGIn();
	_P->outgoingData.WriteByte(ClientPacketID::ClientPacketID_CreateNewGuild);

	_P->outgoingData.WriteUnicodeString(desc);
	_P->outgoingData.WriteUnicodeString(name);
	_P->outgoingData.WriteUnicodeString(url);

	std::string temp;

	for (int i = 0; i <= UBound(codex); ++i)
	{
		temp += codex[i] + '\0';
	}

	if (UBound(codex) > 0) temp[UBound(temp)] = L'\0'; //Quitarlo si es necesario agregar el de abajo.
	if (strlen(temp.c_str())) _P->outgoingData.WriteUnicodeString(temp); //temp = left()
}

void WriteRequestGuildLeaderInfo()
{
	cGameData::p_cGIn()->outgoingData.WriteByte(ClientPacketID::ClientPacketID_RequestGuildLeaderInfo);
}

void WriteGuildRequestMembership(std::string guild, std::string app)
{
	cGameData* _P = cGameData::p_cGIn();
	_P->outgoingData.WriteByte(ClientPacketID::ClientPacketID_GuildRequestMembership);
	_P->outgoingData.WriteUnicodeString(guild);
	_P->outgoingData.WriteUnicodeString(app);
}

void WriteGuildAcceptNewMember(std::string username)
{
	cGameData* _P = cGameData::p_cGIn();
	_P->outgoingData.WriteByte(ClientPacketID::ClientPacketID_GuildAcceptNewMember);
	_P->outgoingData.WriteUnicodeString(username);
}

void WriteGuildRejectNewMember(std::string username, std::string reason)
{
	cGameData* _P = cGameData::p_cGIn();
	_P->outgoingData.WriteByte(ClientPacketID::ClientPacketID_GuildRejectNewMember);
	_P->outgoingData.WriteUnicodeString(username);
	_P->outgoingData.WriteUnicodeString(reason);
}

void WriteInvisible()
{
    cGameData::p_cGIn()->outgoingData.WriteByte(ClientPacketID::ClientPacketID_GMCommands);
    cGameData::p_cGIn()->outgoingData.WriteByte(eGMCommands::eGMCommands_invisible);
}

void WriteTalk(std::string chat)
{
	cGameData* _P = cGameData::p_cGIn();
	_P->outgoingData.WriteByte(ClientPacketID::ClientPacketID_Talk);
	_P->outgoingData.WriteUnicodeString(chat);
}

void WriteQuit()
{
	cGameData::p_cGIn()->outgoingData.WriteByte(ClientPacketID::ClientPacketID_Quit);
}

void FlushBuffer()
{
    int sizebuff = cGameData::p_cGIn()->outgoingData.length();

    if (sizebuff <= 0)
    {
        return;
    }

    std::string sndData = cGameData::p_cGIn()->outgoingData.ReadBinaryFixed(sizebuff);
    char* c_sndData = new char[sizebuff + 1];
    std::copy(sndData.begin(), sndData.end(), c_sndData);

    cWinsock::p_cGIn()->sendMessage(cWinsock::p_cGIn()->Socket, c_sndData, sizebuff);
    delete [] c_sndData;
}
