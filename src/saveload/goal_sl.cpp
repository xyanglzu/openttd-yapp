/* $Id: goal_sl.cpp 23737 2012-01-03 20:37:56Z truebrain $ */

/*
 * This file is part of OpenTTD.
 * OpenTTD is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenTTD is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenTTD. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file goal_sl.cpp Code handling saving and loading of goals */

#include "../stdafx.h"
#include "../goal_base.h"

#include "saveload.h"

static const SaveLoad _goals_desc[] = {
	    SLE_VAR(Goal, company, SLE_UINT16),
	    SLE_VAR(Goal, type,    SLE_UINT16),
	    SLE_VAR(Goal, dst,     SLE_UINT32),
	    SLE_STR(Goal, text,    SLE_STR | SLF_ALLOW_CONTROL, 0),
	    SLE_END()
};

static void Save_GOAL()
{
	Goal *s;
	FOR_ALL_GOALS(s) {
		SlSetArrayIndex(s->index);
		SlObject(s, _goals_desc);
	}
}

static void Load_GOAL()
{
	int index;
	while ((index = SlIterateArray()) != -1) {
		Goal *s = new (index) Goal();
		SlObject(s, _goals_desc);
	}
}

extern const ChunkHandler _goal_chunk_handlers[] = {
	{ 'GOAL', Save_GOAL, Load_GOAL, NULL, NULL, CH_ARRAY | CH_LAST},
};
