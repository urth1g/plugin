//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//
//===========================================================================//

#include <stdio.h>

// #define GAME_DLL
// #ifdef GAME_DLL
// #include "cbase.h"
// #endif

#include <stdio.h>
#include "interface.h"
#include "filesystem.h"
#include "engine/iserverplugin.h"
#include "eiface.h"
#include "igameevents.h"
#include "convar.h"
#include "Color.h"
#include "vstdlib/random.h"
#include "engine/IEngineTrace.h"
#include "tier2/tier2.h"
#include "game/server/iplayerinfo.h"
#include <typeinfo>

//#define SAMPLE_TF2_PLUGIN
#ifdef SAMPLE_TF2_PLUGIN

#endif
// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

/**
 * vim: set ts=4 sw=4 tw=99 noet :
 * ======================================================
 * Metamod:Source Sample Plugin
 * Written by AlliedModders LLC.
 * ======================================================
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from
 * the use of this software.
 *
 * This sample plugin is public domain.
 */

// define gameevents

IGameEventManager2 *gameevents = NULL;

class CPlayerDeathEvent : public IGameEventListener2
{
public:
    virtual void FireGameEvent(IGameEvent* event)
    {
        // Check if the event is a player death event
        if (strcmp(event->GetName(), "player_death") == 0)
        {
            // Get the index of the player who died
            int victim = event->GetInt("userid");
            // Get the name of the player who died
            const char* victimName = event->GetString("victim_name");
            // Get the index of the player or entity that killed the victim
            int attacker = event->GetInt("attacker");
            // Get the name of the attacker
            const char* attackerName = event->GetString("attacker_name");
            // Get the cause of death
            const char* weapon = event->GetString("weapon");
            // Handle the player death here
            // ...
        }
    }
    virtual int GetEventDebugID(void)
    {
        return EVENT_DEBUG_ID_INIT;
    }
};

CPlayerDeathEvent g_PlayerDeathEvent;


class CServerPlugin : public IServerPluginCallbacks
{
public:
    virtual bool Load(CreateInterfaceFn interfaceFactory, CreateInterfaceFn gameServerFactory)
    {
        // Hook into the game events interface
        gameevents = (IGameEventManager2*)gameServerFactory(INTERFACEVERSION_GAMEEVENTSMANAGER2, NULL);
        if (!gameevents)
        {
            return false;
        }
        // Register the player death event
        gameevents->AddListener(&g_PlayerDeathEvent, "player_death", false);
        return true;
    }
    virtual void Unload(void)
    {
        // Unregister the player death event
        gameevents->RemoveListener(&g_PlayerDeathEvent);
    }
    virtual void Pause(void)
    {
    }
    virtual void UnPause(void)
    {
    }
    virtual const char* GetPluginDescription(void)
    {
        return "Server Plugin Sample 1.0, by AlliedModders LLC";
    }
    virtual void LevelInit(char const* pMapName)
    {
    }
    virtual void ServerActivate(edict_t* pEdictList, int edictCount, int clientMax)
    {
    }
    virtual void GameFrame(bool simulating)
    {
    }
    virtual void LevelShutdown(void)
    {
    }
    virtual void ClientActive(edict_t* pEntity)
    {
    }
    virtual void ClientDisconnect(edict_t* pEntity)
    {
    }
    virtual void ClientPutInServer(edict_t* pEntity, char const* playername)
    {
    }
    virtual void SetCommandClient(int index)
    {
    }
    virtual void ClientSettingsChanged(edict_t* pEdict)
    {
    }
    virtual PLUGIN_RESULT ClientConnect(bool* bAllowConnect, edict_t* pEntity, const char* pszName, const char* pszAddress, char* reject, int maxrejectlen)
    {
        return PLUGIN_CONTINUE;
    }
    virtual PLUGIN_RESULT ClientCommand(edict_t* pEntity, const CCommand& args)
    {
        return PLUGIN_CONTINUE;
    }
    virtual PLUGIN_RESULT NetworkIDValidated(const char* pszUserName, const char* pszNetworkID)
    {
        return PLUGIN_CONTINUE;
    }
    virtual void OnQueryCvarValueFinished(QueryCvarCookie_t iCookie, edict_t* pPlayerEntity, EQueryCvarValueStatus eStatus, const char* pCvarName, const char* pCvarValue)
    {
    }
    virtual void OnEdictAllocated(edict_t* edict)
    {
    }
    virtual void OnEdictFreed(const edict_t* edict)
    {
    }
};
