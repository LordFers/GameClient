#ifndef _H_FMAIN_
#define _H_FMAIN_

void FMain_Load();
void FMain_UnLoad();
void FMain_Visible(bool);
void FMain_Menu_Visible(bool);
void FMain_GuildList_Visible(bool);
void FMain_GuildNews_setText(const char*);
void FMain_Reload_GuildList();
void FMain_Reload_GuildMember();
void FMain_Reload_GuildAspirantes();
void FMain_GuildLeader_Visible(bool, bool);
void FMain_setExpBar(float);
void FMain_AddItem_Console(const char*, int, bool, bool);
void FMain_SendText();

//Eventos independientes
bool FMain_GetActive_SendText();
#endif