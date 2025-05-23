#include "stdafx.h"
#include "config.h"
#include "char.h"
#include "char_manager.h"
#include "questmanager.h"
#include "questevent.h"

namespace quest
{
	void CancelTimerEvent(LPEVENT * ppEvent)
	{
		event_cancel(ppEvent);
	}

	EVENTFUNC(quest_server_timer_event)
	{
		quest_server_event_info * info = dynamic_cast<quest_server_event_info *>( event->info );

		if ( info == NULL )
		{
			sys_err( "quest_server_timer_event> <Factor> Null pointer" );
			return 0;
		}

		CQuestManager& q = CQuestManager::instance();

		if (!q.ServerTimer(info->npc_id, info->arg))
			return passes_per_sec / 2 + 1;

		if (0 == info->time_cycle)
			q.ClearServerTimerNotCancel(info->name, info->arg);

		return info->time_cycle;
	}

	EVENTFUNC(quest_timer_event)
	{
		quest_event_info * info = dynamic_cast<quest_event_info *>( event->info );

		if ( info == NULL )
		{
			sys_err( "quest_timer_event> <Factor> Null pointer" );
			return 0;
		}

		CQuestManager & q = CQuestManager::instance();

		if (CHARACTER_MANAGER::instance().FindByPID(info->player_id))
		{
			if (!CQuestManager::instance().Timer(info->player_id, info->npc_id))
				return (passes_per_sec / 2 + 1);

			if (info->time_cycle)
				return info->time_cycle;
		}

		PC * pPC = q.GetPC(info->player_id);
		if (pPC)
			pPC->RemoveTimerNotCancel(info->name);
		else
			sys_err("quest::PC pointer null. player_id: %u", info->player_id);

		return 0;
	}

	LPEVENT quest_create_server_timer_event(const char * name, double when, unsigned int timernpc, bool loop, unsigned int arg)
	{
		long ltime_cycle = (long) (rint(PASSES_PER_SEC(when)));

		quest_server_event_info* info = AllocEventInfo<quest_server_event_info>();

		info->npc_id = timernpc;
		info->time_cycle = loop ? ltime_cycle : 0;
		info->arg = arg;
		info->name = name;

		return event_create(quest_server_timer_event, info, ltime_cycle);
	}

	LPEVENT quest_create_timer_event(const char * name, unsigned int player_id, double when, unsigned int npc_id, bool loop)
	{
		long ltime_cycle = (int) (rint(PASSES_PER_SEC(when)));

		quest_event_info* info = AllocEventInfo<quest_event_info>();

		info->player_id		= player_id;
		info->npc_id		= npc_id;
		info->name			= name;

		sys_log(0, "QUEST timer name %s cycle %d pc %u npc %u loop? %d", name ? name : "<noname>", ltime_cycle, player_id, npc_id, loop ? 1 : 0);

		info->time_cycle	= loop ? ltime_cycle : 0;
		return event_create(quest_timer_event, info, ltime_cycle);
	}
}
//martysama0134's a288e6779da68f768431f9975e780da3
