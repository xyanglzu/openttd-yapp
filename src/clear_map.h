/* $Id: clear_map.h 23595 2011-12-19 17:48:04Z rubidium $ */

/*
 * This file is part of OpenTTD.
 * OpenTTD is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenTTD is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenTTD. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file clear_map.h Map accessors for 'clear' tiles */

#ifndef CLEAR_MAP_H
#define CLEAR_MAP_H

#include "bridge_map.h"
#include "industry_type.h"

/**
 * Ground types. Valid densities in comments after the enum.
 */
enum ClearGround {
	CLEAR_GRASS  = 0, ///< 0-3
	CLEAR_ROUGH  = 1, ///< 3
	CLEAR_ROCKS  = 2, ///< 3
	CLEAR_FIELDS = 3, ///< 3
	CLEAR_SNOW   = 4, ///< 0-3
	CLEAR_DESERT = 5, ///< 1,3
};


/**
 * Test if a tile is covered with snow.
 * @param t the tile to check
 * @pre IsTileType(t, MP_CLEAR)
 * @return whether the tile is covered with snow.
 */
static inline bool IsSnowTile(TileIndex t)
{
	assert(IsTileType(t, MP_CLEAR));
	return HasBit(GetTile(t)->m3, 4);
}

/**
 * Get the type of clear tile but never return CLEAR_SNOW.
 * @param t the tile to get the clear ground type of
 * @pre IsTileType(t, MP_CLEAR)
 * @return the ground type
 */
static inline ClearGround GetRawClearGround(TileIndex t)
{
	assert(IsTileType(t, MP_CLEAR));
	return (ClearGround)GB(GetTile(t)->m5, 2, 3);
}

/**
 * Get the type of clear tile.
 * @param t the tile to get the clear ground type of
 * @pre IsTileType(t, MP_CLEAR)
 * @return the ground type
 */
static inline ClearGround GetClearGround(TileIndex t)
{
	if (IsSnowTile(t)) return CLEAR_SNOW;
	return GetRawClearGround(t);
}

/**
 * Set the type of clear tile.
 * @param t  the tile to set the clear ground type of
 * @param ct the ground type
 * @pre IsTileType(t, MP_CLEAR)
 */
static inline bool IsClearGround(TileIndex t, ClearGround ct)
{
	return GetClearGround(t) == ct;
}


/**
 * Get the density of a non-field clear tile.
 * @param t the tile to get the density of
 * @pre IsTileType(t, MP_CLEAR)
 * @return the density
 */
static inline uint GetClearDensity(TileIndex t)
{
	assert(IsTileType(t, MP_CLEAR));
	return GB(GetTile(t)->m5, 0, 2);
}

/**
 * Increment the density of a non-field clear tile.
 * @param t the tile to increment the density of
 * @param d the amount to increment the density with
 * @pre IsTileType(t, MP_CLEAR)
 */
static inline void AddClearDensity(TileIndex t, int d)
{
	assert(IsTileType(t, MP_CLEAR)); // XXX incomplete
	GetTile(t)->m5 += d;
}

/**
 * Set the density of a non-field clear tile.
 * @param t the tile to set the density of
 * @param d the new density
 * @pre IsTileType(t, MP_CLEAR)
 */
static inline void SetClearDensity(TileIndex t, uint d)
{
	assert(IsTileType(t, MP_CLEAR));
	SB(GetTile(t)->m5, 0, 2, d);
}


/**
 * Get the counter used to advance to the next clear density/field type.
 * @param t the tile to get the counter of
 * @pre IsTileType(t, MP_CLEAR)
 * @return the value of the counter
 */
static inline uint GetClearCounter(TileIndex t)
{
	assert(IsTileType(t, MP_CLEAR));
	return GB(GetTile(t)->m5, 5, 3);
}

/**
 * Increments the counter used to advance to the next clear density/field type.
 * @param t the tile to increment the counter of
 * @param c the amount to increment the counter with
 * @pre IsTileType(t, MP_CLEAR)
 */
static inline void AddClearCounter(TileIndex t, int c)
{
	assert(IsTileType(t, MP_CLEAR)); // XXX incomplete
	GetTile(t)->m5 += c << 5;
}

/**
 * Sets the counter used to advance to the next clear density/field type.
 * @param t the tile to set the counter of
 * @param c the amount to set the counter to
 * @pre IsTileType(t, MP_CLEAR)
 */
static inline void SetClearCounter(TileIndex t, uint c)
{
	assert(IsTileType(t, MP_CLEAR)); // XXX incomplete
	SB(GetTile(t)->m5, 5, 3, c);
}


/**
 * Sets ground type and density in one go, also sets the counter to 0
 * @param t       the tile to set the ground type and density for
 * @param type    the new ground type of the tile
 * @param density the density of the ground tile
 * @pre IsTileType(t, MP_CLEAR)
 */
static inline void SetClearGroundDensity(TileIndex t, ClearGround type, uint density)
{
	assert(IsTileType(t, MP_CLEAR)); // XXX incomplete
	GetTile(t)->m5 = 0 << 5 | type << 2 | density;
}


/**
 * Get the field type (production stage) of the field
 * @param t the field to get the type of
 * @pre GetClearGround(t) == CLEAR_FIELDS
 * @return the field type
 */
static inline uint GetFieldType(TileIndex t)
{
	assert(GetClearGround(t) == CLEAR_FIELDS);
	return GB(GetTile(t)->m3, 0, 4);
}

/**
 * Set the field type (production stage) of the field
 * @param t the field to get the type of
 * @param f the field type
 * @pre GetClearGround(t) == CLEAR_FIELDS
 */
static inline void SetFieldType(TileIndex t, uint f)
{
	assert(GetClearGround(t) == CLEAR_FIELDS); // XXX incomplete
	SB(GetTile(t)->m3, 0, 4, f);
}

/**
 * Get the industry (farm) that made the field
 * @param t the field to get creating industry of
 * @pre GetClearGround(t) == CLEAR_FIELDS
 * @return the industry that made the field
 */
static inline IndustryID GetIndustryIndexOfField(TileIndex t)
{
	assert(GetClearGround(t) == CLEAR_FIELDS);
	return(IndustryID) GetTile(t)->m2;
}

/**
 * Set the industry (farm) that made the field
 * @param t the field to get creating industry of
 * @param i the industry that made the field
 * @pre GetClearGround(t) == CLEAR_FIELDS
 */
static inline void SetIndustryIndexOfField(TileIndex t, IndustryID i)
{
	assert(GetClearGround(t) == CLEAR_FIELDS);
	GetTile(t)->m2 = i;
}


/**
 * Is there a fence at the south eastern border?
 * @param t the tile to check for fences
 * @pre IsClearGround(t, CLEAR_FIELDS)
 * @return 0 if there is no fence, otherwise the fence type
 */
static inline uint GetFenceSE(TileIndex t)
{
	assert(IsClearGround(t, CLEAR_FIELDS));
	return GB(GetTile(t)->m4, 2, 3);
}

/**
 * Sets the type of fence (and whether there is one) for the south
 * eastern border.
 * @param t the tile to check for fences
 * @param h 0 if there is no fence, otherwise the fence type
 * @pre IsClearGround(t, CLEAR_FIELDS)
 */
static inline void SetFenceSE(TileIndex t, uint h)
{
	assert(IsClearGround(t, CLEAR_FIELDS));
	SB(GetTile(t)->m4, 2, 3, h);
}

/**
 * Is there a fence at the south western border?
 * @param t the tile to check for fences
 * @pre IsClearGround(t, CLEAR_FIELDS)
 * @return 0 if there is no fence, otherwise the fence type
 */
static inline uint GetFenceSW(TileIndex t)
{
	assert(IsClearGround(t, CLEAR_FIELDS));
	return GB(GetTile(t)->m4, 5, 3);
}

/**
 * Sets the type of fence (and whether there is one) for the south
 * western border.
 * @param t the tile to check for fences
 * @param h 0 if there is no fence, otherwise the fence type
 * @pre IsClearGround(t, CLEAR_FIELDS)
 */
static inline void SetFenceSW(TileIndex t, uint h)
{
	assert(IsClearGround(t, CLEAR_FIELDS));
	SB(GetTile(t)->m4, 5, 3, h);
}

/**
 * Is there a fence at the north eastern border?
 * @param t the tile to check for fences
 * @pre IsClearGround(t, CLEAR_FIELDS)
 * @return 0 if there is no fence, otherwise the fence type
 */
static inline uint GetFenceNE(TileIndex t)
{
	assert(IsClearGround(t, CLEAR_FIELDS));
	return GB(GetTile(t)->m3, 5, 3);
}

/**
 * Sets the type of fence (and whether there is one) for the north
 * eastern border.
 * @param t the tile to check for fences
 * @param h 0 if there is no fence, otherwise the fence type
 * @pre IsClearGround(t, CLEAR_FIELDS)
 */
static inline void SetFenceNE(TileIndex t, uint h)
{
	assert(IsClearGround(t, CLEAR_FIELDS));
	SB(GetTile(t)->m3, 5, 3, h);
}

/**
 * Is there a fence at the north western border?
 * @param t the tile to check for fences
 * @pre IsClearGround(t, CLEAR_FIELDS)
 * @return 0 if there is no fence, otherwise the fence type
 */
static inline uint GetFenceNW(TileIndex t)
{
	assert(IsClearGround(t, CLEAR_FIELDS));
	return GB(GetTileEx(t)->m6, 2, 3);
}

/**
 * Sets the type of fence (and whether there is one) for the north
 * western border.
 * @param t the tile to check for fences
 * @param h 0 if there is no fence, otherwise the fence type
 * @pre IsClearGround(t, CLEAR_FIELDS)
 */
static inline void SetFenceNW(TileIndex t, uint h)
{
	assert(IsClearGround(t, CLEAR_FIELDS));
	SB(GetTileEx(t)->m6, 2, 3, h);
}


/**
 * Make a clear tile.
 * @param t       the tile to make a clear tile
 * @param g       the type of ground
 * @param density the density of the grass/snow/desert etc
 */
static inline void MakeClear(TileIndex t, ClearGround g, uint density)
{
	/* If this is a non-bridgeable tile, clear the bridge bits while the rest
	 * of the tile information is still here. */
	if (!MayHaveBridgeAbove(t)) SB(GetTileEx(t)->m6, 6, 2, 0);

	SetTileType(t, MP_CLEAR);
	GetTile(t)->m1 = 0;
	SetTileOwner(t, OWNER_NONE);
	GetTile(t)->m2 = 0;
	GetTile(t)->m3 = 0;
	GetTile(t)->m4 = 0 << 5 | 0 << 2;
	SetClearGroundDensity(t, g, density); // Sets m5
	SB(GetTileEx(t)->m6, 2, 4, 0); // Other bits are "tropic zone" and "bridge above"
	GetTileEx(t)->m7 = 0;
}


/**
 * Make a (farm) field tile.
 * @param t          the tile to make a farm field
 * @param field_type the 'growth' level of the field
 * @param industry   the industry this tile belongs to
 */
static inline void MakeField(TileIndex t, uint field_type, IndustryID industry)
{
	SetTileType(t, MP_CLEAR);
	GetTile(t)->m1 = 0;
	SetTileOwner(t, OWNER_NONE);
	GetTile(t)->m2 = industry;
	GetTile(t)->m3 = field_type;
	GetTile(t)->m4 = 0 << 5 | 0 << 2;
	SetClearGroundDensity(t, CLEAR_FIELDS, 3);
	SB(GetTileEx(t)->m6, 2, 4, 0);
	GetTileEx(t)->m7 = 0;
}

/**
 * Make a snow tile.
 * @param t the tile to make snowy
 * @param density The density of snowiness.
 * @pre GetClearGround(t) != CLEAR_SNOW
 */
static inline void MakeSnow(TileIndex t, uint density = 0)
{
	assert(GetClearGround(t) != CLEAR_SNOW);
	SetBit(GetTile(t)->m3, 4);
	if (GetRawClearGround(t) == CLEAR_FIELDS) {
		SetClearGroundDensity(t, CLEAR_GRASS, density);
	} else {
		SetClearDensity(t, density);
	}
}

/**
 * Clear the snow from a tile and return it to its previous type.
 * @param t the tile to clear of snow
 * @pre GetClearGround(t) == CLEAR_SNOW
 */
static inline void ClearSnow(TileIndex t)
{
	assert(GetClearGround(t) == CLEAR_SNOW);
	ClrBit(GetTile(t)->m3, 4);
	SetClearDensity(t, 3);
}

#endif /* CLEAR_MAP_H */
