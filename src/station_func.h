/* $Id: station_func.h 24840 2012-12-23 15:38:54Z peter1138 $ */

/*
 * This file is part of OpenTTD.
 * OpenTTD is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenTTD is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenTTD. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file station_func.h Functions related to stations. */

#ifndef STATION_FUNC_H
#define STATION_FUNC_H

#include "sprite.h"
#include "rail_type.h"
#include "road_type.h"
#include "economy_func.h"
#include "rail.h"
#include "order_type.h"

void ModifyStationRatingAround(TileIndex tile, Owner owner, int amount, uint radius);

void FindStationsAroundTiles(const TileArea &location, StationList *stations);

void ShowStationViewWindow(StationID station);
void UpdateAllStationVirtCoords();

CargoArray GetProductionAroundTiles(TileIndex tile, int w, int h, int rad);
CargoArray GetAcceptanceAroundTiles(TileIndex tile, int w, int h, int rad, uint32 *always_accepted = NULL);

CargoArray GetProductionRateAroundTiles(TileIndex tile, int w, int h, int rad);
CargoArray GetAcceptanceRateAroundTiles(TileIndex tile, int w, int h, int rad);

void UpdateStationAcceptance(Station *st, bool show_msg);
uint UpdateStationWaiting(Station *st, CargoID type, uint amount, SourceType source_type, SourceID source_id, TileIndex dest_tile = INVALID_TILE, SourceType dest_type = ST_INDUSTRY, SourceID dest_id = INVALID_SOURCE, OrderID next_hop = INVALID_ORDER, StationID next_unload = INVALID_STATION, byte flags = 0);

const DrawTileSprites *GetStationTileLayout(StationType st, byte gfx);
void StationPickerDrawSprite(int x, int y, StationType st, RailType railtype, RoadType roadtype, int image);

bool HasStationInUse(StationID station, bool include_company, CompanyID company);

void DeleteOilRig(TileIndex t);

/* Check if a rail station tile is traversable. */
bool IsStationTileBlocked(TileIndex tile);

bool CanStationTileHavePylons(TileIndex tile);
bool CanStationTileHaveWires(TileIndex tile);

void UpdateAirportsNoise();

bool SplitGroundSpriteForOverlay(const TileInfo *ti, SpriteID *ground, RailTrackOffset *overlay_offset);

/**
 * Calculates the maintenance cost of a number of station tiles.
 * @param num Number of station tiles.
 * @return Total cost.
 */
static inline Money StationMaintenanceCost(uint32 num)
{
	return (_price[PR_INFRASTRUCTURE_STATION] * num * (1 + IntSqrt(num))) >> 7; // 7 bits scaling.
}

Money AirportMaintenanceCost(Owner owner);

#endif /* STATION_FUNC_H */
