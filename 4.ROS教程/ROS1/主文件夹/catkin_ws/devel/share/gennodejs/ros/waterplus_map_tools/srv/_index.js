
"use strict";

let SaveWaypoints = require('./SaveWaypoints.js')
let GetNumOfWaypoints = require('./GetNumOfWaypoints.js')
let GetWaypointByName = require('./GetWaypointByName.js')
let GetWaypointByIndex = require('./GetWaypointByIndex.js')
let AddNewWaypoint = require('./AddNewWaypoint.js')
let GetChargerByName = require('./GetChargerByName.js')

module.exports = {
  SaveWaypoints: SaveWaypoints,
  GetNumOfWaypoints: GetNumOfWaypoints,
  GetWaypointByName: GetWaypointByName,
  GetWaypointByIndex: GetWaypointByIndex,
  AddNewWaypoint: AddNewWaypoint,
  GetChargerByName: GetChargerByName,
};
