#include "odv_scb_disassembler.h"

struct ODVExternalFunction extern_func[NB_EXTERNAL_FUNC] = {
    /* 0x00 */    {"IStartDialog", 0x01, { {0x04, "ID_DIALOGUE"} }, "Play a dialogue"},
    /* 0x01 */    {"ISetCameraScrollTo", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x02 */    {"ISetCameraScrollSlowlyTo", 0x02, { {0x04, "UNK"}, {0x04, "UNK"} }, "UNK"},
    /* 0x03 */    {"ISetCameraJumpTo", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x04 */    {"ISetZoomLevel", 0x01, { {0x04, "FLOAT"} }, "Change zoom level"},
    /* 0x05 */    {"IDisplayMap", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x06 */    {"IPrintConsole", 0x01, { {0x04, "UNK"} }, "Output text on surface"},
    /* 0x07 */    {"IDisplayConsole", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x08 */    {"IIsActorEqual", 0x02, { {0x04, "UNK"}, {0x04, "UNK"} }, "Compare two values"},
    /* 0x09 */    {"IIsAnyCivilianDead", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x0A */    {"IIsAnyEnemyDead", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x0B */    {"IGetOverallEnemyAlert", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x0C */    {"IGetOverallCivilianAlert", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x0D */    {"IFreezeAll", 0x01, { {0x04, "UNK"} }, "Freeze actor element"},
    /* 0x0E */    {"IInflictPain", 0x03, { {0x04, "UNK"} , {0x04, "UNK"}, {0x04, "UNK"}}, "Inflict pain to actor"},
    /* 0x0F */    {"IGetNumberOfActorsInEngine", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x10 */    {"IGetActor", 0x01, { {0x04, "ACTOR_ID"} }, "Acces an actor by ID"},
    /* 0x11 */    {"IGetLocation", 0x01, { {0x04, "LOCATION_ID"} }, "Acces a location by ID"},
    /* 0x12 */    {"IIsActorAnimation", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x13 */    {"IIsActorObject", 0x01, { {0x04, "ACTOR"} }, "Test an actor element (flags & 0x03 == 0x01)"},
    /* 0x14 */    {"IIsActorCharacter", 0x01, { {0x04, "ACTOR"} }, "Test an actor element (flags & 0x03 == 0x03)"},
    /* 0x15 */    {"IIsActorPC", 0x01, { {0x04, "ACTOR"} }, "Test an actor element (flags & 0x0F == 0x0F)"},
    /* 0x16 */    {"IIsActorNPC", 0x01, { {0x04, "ACTOR"} }, "Test an actor element (flags & 0x0F == 0x07)"},
    /* 0x17 */    {"IIsActorEnemy", 0x01, { {0x04, "ACTOR"} }, "Test an actor element (flags & 0x1F == 0x17)"},
    /* 0x18 */    {"IIsActorCivilian", 0x01, { {0x04, "ACTOR"} }, "Test an actor element (flags & 0x1F == 0x07)"},
    /* 0x19 */    {"IIsActorAnimal", 0x01, { {0x04, "ACTOR"} }, "Test an actor element (flags & 0x07 == 0x03)"},
    /* 0x1A */    {"IIsNull", 0x01, { {0x04, "UNK"} }, "Test if NULL"},
    /* 0x1B */    {"IGetActorPosture", 0x01, { {0x04, "ACTOR"} }, "Get the posture of a human actor"},
    /* 0x1C */    {"ISetActorPosture", 0x01, { {0x04, "ACTOR"}, {0x04, "POSTURE"} }, "Set the posture of a human actor"},
    /* 0x1D */    {"IGetCooper", 0x00, { {0x00} }, "Get Cooper"},
    /* 0x1E */    {"IGetSam", 0x00, { {0x00} }, "Get Sam"},
    /* 0x1F */    {"IGetDoc", 0x00, { {0x00} }, "Get Doc"},
    /* 0x20 */    {"IGetKate", 0x00, { {0x00} }, "Get Kate"},
    /* 0x21 */    {"IGetSanchez", 0x00, { {0x00} }, "Get Sanchez"},
    /* 0x22 */    {"IGetMia", 0x00, { {0x00} }, "Get Mia"},
    /* 0x23 */    {"IGetActorLocation", 0x01, { {0x04, "ACTOR"} }, "Get location information"},
    /* 0x24 */    {"ISetActorLocation", 0x02, { {0x04, "ACTOR"}, {0x04, "UNK"} }, "Set location"},
    /* 0x25 */    {"IIsInside", 0x02, { {0x04, "ACTOR"}, {0x04, "UNK"} }, "Check if a character is inside a location (must be a sector)"},
    /* 0x26 */    {"IIsInsideBuilding", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x27 */    {"IGetAnyActorInside", 0x01, { {0x04, "UNK"} }, "Check if any character is inside a location (must be a sector)"},
    /* 0x28 */    {"ISwitchProfile", 0x01, { {0x04, "ACTOR"} }, "Switch profile"},
    /* 0x29 */    {"IGetMovementStyle", 0x01, { {0x04, "ACTOR"} }, "Get the movement style of an actor"},
    /* 0x2A */    {"IDeactivate", 0x01, { {0x04, "ACTOR"} }, "Desactivate an actor"},
    /* 0x2B */    {"IActivate", 0x01, { {0x04, "ACTOR"} }, "Activate an actor"},
    /* 0x2C */    {"ISetActionAvailable", 0x03, { {0x04, "ACTOR"}, {0x04, "ACTION"}, {0x04, "AVAILABILITY"} }, "Set the availability of an action of an actor"},
    /* 0x2D */    {"IIsActionAvailable", 0x02, { {0x04, "ACTOR"}, {0x04, "AVAILABILITY"} }, "Set the availability of an actor"},
    /* 0x2E */    {"ISetPersistentProperty", 0x03, { {0x04, "ACTOR"}, {0x04, "PROPERTY"}, {0x04, "NUMBER"} }, "Set the property of an actor"},
    /* 0x2F */    {"IGetPersistentProperty", 0x02, { {0x04, "ACTOR"}, {0x04, "PROPERTY"} }, "Get the property of an actor"},
    /* 0x30 */    {"ISetAIAlertStatus", 0x02, { {0x04, "ACTOR"}, {0x04, "ALERT_STATE"}  }, "Set alert state of a NPC"},
    /* 0x31 */    {"IGetAIAlertStatus", 0x01, { {0x04, "ACTOR"} }, "Get alert state of a NPC"},
    /* 0x32 */    {"ISetAIState", 0x02, { {0x04, "ACTOR"}, {0x04, "AI_STATE"} }, "Set AI state"},
    /* 0x33 */    {"IGetAIState", 0x01, { {0x04, "ACTOR"} }, "Get AI state"},
    /* 0x34 */    {"ISetAIAttitude", 0x02, { {0x04, "ACTOR"}, {0x04, "ATTITUDE"} }, "Set attitude of an NPC"},
    /* 0x35 */    {"IGetAIAttitude", 0x01, { {0x04, "ACTOR"} }, "Get attitude of an NPC"},
    /* 0x36 */    {"ISetAILevel", 0x03, { {0x04, "ACTOR"}, {0x04, "UNK"}, {0x04, "UNK"} }, "Set AI level of an NPC"},
    /* 0x37 */    {"ISetViewCone", 0x02, { {0x04, "ACTOR"}, {0x04, "UNK"} }, "Set viewcone of an NPC"},
    /* 0x38 */    {"IStareActor", 0x03, { {0x04, "ACTOR"},  {0x04, "UNK"},  {0x04, "UNK"} }, "Get stare actor command"},
    /* 0x39 */    {"IStareLocation", 0x03, { {0x04, "ACTOR"},  {0x04, "UNK"},  {0x04, "UNK"} }, "Get stare location command"},
    /* 0x3A */    {"IAssignPath", 0x02, { {0x04, "ACTOR"} , {0x04, "UNK"} }, "Set patrol path for NPC"},
    /* 0x3B */    {"IAssignPost", 0x03, { {0x04, "ACTOR"},  {0x04, "UNK"},  {0x04, "UNK"} }, "Set post for NPC"},
    /* 0x3C */    {"ILockAI", 0x02, { {0x04, "ACTOR"}, {0x04, "UNK"} }, "Lock AI"},
    /* 0x3D */    {"IUnlockAI", 0x01, { {0x04, "ACTOR"} }, "Unlock AI"},
    /* 0x3E */    {"IForceBattleDecision", 0x02, { {0x04, "ACTOR"} , {0x04, "UNK"} }, "Set battle decision"},
    /* 0x3F */    {"IMakeNoise", 0x02, { {0x04, "UNK"}, {0x04, "UNK"}}, "Set Noise"},
    /* 0x40 */    {"IFreeze", 0x02, { {0x04, "UNK"}, {0x04, "UNK"} }, "Freeze actor element"},
    /* 0x41 */    {"IGetTheRider", 0x01, { {0x04, "UNK"} }, "Get rider"},
    /* 0x42 */    {"IGetTheHorse", 0x01, { {0x04, "UNK"} }, "Get horse"},
    /* 0x43 */    {"IIsAnimationActive", 0x01, { {0x04, "UNK"} }, "IsAnimationActive"},
    /* 0x44 */    {"ISetAnimationState", 0x02, { {0x04, "ACTOR"}, {0x04, "UNK"} }, "SetAnimationState"},
    /* 0x45 */    {"IIsPatchApplied", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x46 */    {"IApplyPatch", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x47 */    {"IIsHorseUsed", 0x01, { {0x04, "UNK"} }, "IsHorseUsed"},
    /* 0x48 */    {"IStartSequenceRecording", 0x00, { {0x00} }, "UNK"},
    /* 0x49 */    {"IEndSequenceRecording", 0x01, { {0x04, "UNK"} }, "Launch sequence"},
    /* 0x4A */    {"IIncrementSequenceLevel", 0x00, { {0x00} }, "Increment sequence level"},
    /* 0x4B */    {"IStart", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x4C */    {"IThanx", 0x01, { {0x04, "UNK"} }, "Launch sequence (2)"},
    /* 0x4D */    {"IThen", 0x00, { {0x00} }, "Increment sequence level (2)"},
    /* 0x4E */    {"IRecordCameraScrollTo", 0x01, { {0x04, "UNK"} }, "Declare fire sequence"},
    /* 0x4F */    {"IRecordCameraJumpTo", 0x01, { {0x04, "UNK"} }, "Declare fire sequence (2)"},
    /* 0x50 */    {"IRecordSetZoom", 0x01, { {0x04, "UNK"} }, "Declare fire sequence (3)"},
    /* 0x51 */    {"IRecordDisplayMap", 0x01, { {0x04, "UNK"} }, "Declare fire sequence (4)"},
    /* 0x52 */    {"IRecordStartBriefing", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x53 */    {"IRecordEndBriefing", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x54 */    {"IRecordActionAvailable", 0x03, { {0x04, "UNK"}, {0x04, "UNK"}, {0x04, "UNK"} }, "Create a action available sequence with a actor"},
    /* 0x55 */    {"IRecordCharacterAvailable", 0x02, { {0x04, "UNK"}, {0x04, "UNK"} }, "Create a action available sequence with a actor"},
    /* 0x56 */    {"IRecordLockCameraOn", 0x01, { {0x04, "UNK"} }, "Create a move sequence with a actor"},
    /* 0x57 */    {"IRecordClearCameraLock", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x58 */    {"IRecordPlayDialog", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x59 */    {"IRecordMove", 0x03, { {0x04, "UNK"}, {0x04, "UNK"}, {0x04, "UNK"} }, "Create move sequence"},
    /* 0x5A */    {"IRecordLeaveGame", 0x03, { {0x04, "UNK"}, {0x04, "UNK"}, {0x04, "UNK"} }, "Create move sequence (2)"},
    /* 0x5B */    {"IRecordTurnTo", 0x02, { {0x04, "UNK"}, {0x04, "UNK"} }, "Create a turn sequence"},
    /* 0x5C */    {"IRecordMountHorse", 0x02, { {0x04, "UNK"}, {0x04, "UNK"} }, "Create a mount sequence"},
    /* 0x5D */    {"IRecordDismountHorse", 0x02, { {0x04, "UNK"}, {0x04, "UNK"} }, "Create a dismount sequence"},
    /* 0x5E */    {"IRecordFireAt", 0x02, { {0x04, "UNK"}, {0x04, "UNK"} }, "Create a fire sequence"},
    /* 0x5F */    {"IRecordPlayAnim", 0x02, { {0x04, "UNK"}, {0x04, "UNK"} }, "Create anim sequence"},
    /* 0x60 */    {"IRecordPlayAnimLoop", 0x02, { {0x04, "UNK"}, {0x04, "UNK"} }, "Play anim sequence"},
    /* 0x61 */    {"IRecordPlayAnimFreeze", 0x02, { {0x04, "UNK"}, {0x04, "UNK"} }, "Declare play anim sequence"},
    /* 0x62 */    {"IRecordLockAI", 0x01, { {0x04, "UNK"} }, "Lock AI method"},
    /* 0x63 */    {"IRecordUnlockAI", 0x01, { {0x04, "UNK"} }, "Unlock AI method"},
    /* 0x64 */    {"IRecordLockUser", 0x00, { {0x00} }, "Declare a fire at sequence"},
    /* 0x65 */    {"IRecordUnLockUser", 0x01, { {0x04, "UNK"} }, "Declare a fire at sequence (2)"},
    /* 0x66 */    {"IRecordTimer", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x67 */    {"IRecordSeekActor", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x68 */    {"IRecordStopSeek", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x69 */    {"IRecordSendCustomEvent", 0x01, { {0x04, "UNK"} }, "DO NOTHING"},
    /* 0x6A */    {"IRecordAction", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x6B */    {"IInitGlobal", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x6C */    {"ISetGlobal", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x6D */    {"IGetGlobal", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x6E */    {"ISuspendAllSoundSources", 0x00, { {0x00} }, "Stop channel"},
    /* 0x6F */    {"IResumeAllSoundSources", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x70 */    {"IGetSoundSource", 0x01, { {0x04, "UNK"} }, "Get sound source"},
    /* 0x71 */    {"IActivateSoundSource", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x72 */    {"IDeactivateSoundSource", 0x01, { {0x04, "UNK"} }, "Stop Channel (2)"},
    /* 0x73 */    {"IDestroySoundSource", 0x01, { {0x04, "UNK"} }, "Stop Channel (3)"},
    /* 0x74 */    {"ICleanFromHisBuildingBeforeTeleport", 0x01, { {0x04, "UNK"} }, "Clean actor"},
    /* 0x75 */    {"IAddToHisNewBuildingAfterTeleport", 0x01, { {0x04, "UNK"} }, "Add actor to a building"},
    /* 0x76 */    {"ICleanFromScriptZoneBeforeTeleport", 0x01, { {0x04, "UNK"} }, "Clean actor (2)"},
    /* 0x77 */    {"IAddToScriptZoneAfterTeleport", 0x01, { {0x04, "UNK"} }, "Add actor to a script zone"},
    /* 0x78 */    {"ILockNearestDoorForPCs", 0x01, { {0x04, "UNK"} }, "Open a door"},
    /* 0x79 */    {"ILockNearestDoorForVillains", 0x01, { {0x04, "UNK"} }, "Open a door (2)"},
    /* 0x7A */    {"ILockNearestDoorForCivilians", 0x01, { {0x04, "UNK"} }, "Open a door (3)"},
    /* 0x7B */    {"IThis", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x7C */    {"IGetActorDirection", 0x01, { {0x04, "UNK"} }, "Get direction of a actor"},
    /* 0x7D */    {"ISetActorDirection", 0x01, { {0x04, "UNK"} }, "Set direction of a actor"},
    /* 0x7E */    {"IStopActor", 0x01, { {0x04, "UNK"} }, "Stop a actor"},
    /* 0x7F */    {"IGetDistance", 0x01, { {0x04, "UNK"} }, "GetDistance"},
    /* 0x80 */    {"IGetCurrentAction", 0x01, { {0x04, "UNK"} }, "GetAction"},
    /* 0x81 */    {"IIsActorCart", 0x01, { {0x04, "UNK"} }, "Test actor element (flag & 0x03) == 0x02"},
    /* 0x82 */    {"ISetPathWalkingStyle", 0x01, { {0x04, "UNK"} }, "Set path walking style"},
    /* 0x83 */    {"IRecordReplaceAnim", 0x01, { {0x04, "UNK"} }, "Create a replace-anim sequence"},
    /* 0x84 */    {"IRecordRestoreAnim", 0x01, { {0x04, "UNK"} }, "Create a restore-anim sequence"},
    /* 0x85 */    {"ISees", 0x01, { {0x04, "UNK"} }, "Test if a NPC see ACTOR"},
    /* 0x86 */    {"IGetActorIndex", 0x01, { {0x04, "UNK"} }, "Get index actor element"},
    /* 0x87 */    {"IJoinArmy", 0x01, { {0x04, "UNK"} }, "JoinArmy"},
    /* 0x88 */    {"IDeclareWar", 0x01, { {0x04, "UNK"} }, "DeclareWar"},
    /* 0x89 */    {"IGetArmy", 0x01, { {0x04, "UNK"} }, "GetArmy"},
    /* 0x8A */    {"ISetSoldierSeesSoldier", 0x01, { {0x04, "UNK"} }, "SetSoldierSeesSoldier"},
    /* 0x8B */    {"ISetSoldierSeesArmy", 0x01, { {0x04, "UNK"} }, "SetSoldierSeesArmy"},
    /* 0x8C */    {"ISetArmySeesSoldier", 0x01, { {0x04, "UNK"} }, "SetArmySeesSoldier"},
    /* 0x8D */    {"ISetArmySeesArmy", 0x01, { {0x04, "UNK"} }, "SetArmySeesArmy"},
    /* 0x8E */    {"IGetNumberOfVisibleSoldiers", 0x01, { {0x04, "UNK"} }, "GetNumberOfVisibleSoldiers"},
    /* 0x8F */    {"IGetVisibleSoldier", 0x01, { {0x04, "UNK"} }, "GetVisibleSoldier"},
    /* 0x90 */    {"IGetNearestVisibleSoldier", 0x01, { {0x04, "UNK"} }, "GetNearestVisibleSoldier"},
    /* 0x91 */    {"ICreateListOfRecentlySeenSoldiers", 0x01, { {0x04, "UNK"} }, "CreateListOfRecentlySeenSoldiers"},
    /* 0x92 */    {"IGetNumberOfRecentlySeenSoldiers", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x93 */    {"IGetRecentlySeenSoldier", 0x01, { {0x04, "UNK"} }, "GetRecentlySeenSoldier"},
    /* 0x94 */    {"IGetNearestRecentlySeenSoldier", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x95 */    {"IPutSnakeOnMap", 0x01, { {0x04, "UNK"} }, "PutSnakeOnMap"},
    /* 0x96 */    {"IPutWatchOnMap", 0x01, { {0x04, "UNK"} }, "PutWatchOnMap"},
    /* 0x97 */    {"IRecordTakeCorpse", 0x01, { {0x04, "UNK"} }, "RecordTakeCorpse"},
    /* 0x98 */    {"IRecordMoveIntoBuilding", 0x01, { {0x04, "UNK"} }, "Walk into a building"},
    /* 0x99 */    {"IRecordCameraMoveTo", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x9A */    {"IRecordEnterBarrel", 0x01, { {0x04, "UNK"} }, "RecordEnterBarrel"},
    /* 0x9B */    {"IRecordLeaveBarrel", 0x01, { {0x04, "UNK"} }, "RecordLeaveBarrel"},
    /* 0x9C */    {"IRecordEnterGame", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x9D */    {"IRecordLeaveCorpse", 0x01, { {0x04, "UNK"} }, "RecordLeaveCorpse"},
    /* 0x9E */    {"ISetUltimateWillOnHorse", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x9F */    {"ICallKnife", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0xA0 */    {"IResetAnim", 0x01, { {0x04, "UNK"} }, "SetAnimationState"},
    /* 0xA1 */    {"IRecordJumpOnHorse", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0xA2 */    {"IEnableHorseUseFor", 0x01, { {0x04, "UNK"} }, "EnableHorseUseFor"},
    /* 0xA3 */    {"IDefineAnimalAlert", 0x01, { {0x04, "UNK"} }, "Define animal alert"},
    /* 0xA4 */    {"IRecordTieCorpse", 0x01, { {0x04, "UNK"} }, "RecordTieCorpse"},
    /* 0xA5 */    {"IPutActorInBulding", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0xA6 */    {"ISetBuildingActive", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0xA7 */    {"IRecordStartMobileElement", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0xA8 */    {"IRecordStopMobileElement", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0xA9 */    {"ISetNearestDoorDocLockPickable", 0x01, { {0x04, "UNK"} }, "Make a door doclockpickable"},
    /* 0xAA */    {"IDisplayHint", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0xAB */    {"IHideHint", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0xAC */    {"IPutActorInBarrel", 0x01, { {0x04, "UNK"} }, "PutActorInBarrel"},
    /* 0xAD */    {"ISetSkipData", 0x01, { {0x04, "UNK"} }, "Skip data ???"},
    /* 0xAE */    {"IForbidHorseForAI", 0x01, { {0x04, "UNK"} }, "Forbid a horse"},
    /* 0xAF */    {"IRecordSpeak", 0x01, { {0x04, "UNK"} }, "Declare a speak sequence"},
    /* 0xB0 */    {"IRecordFireLocation", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0xB1 */    {"IRand", 0x01, { {0x04, "UNK"} }, "Get a random value"},
    /* 0xB2 */    {"IResetPatch", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0xB3 */    {"IPrototypeFilterEvent", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0xB4 */    {"IAddSentence", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0xB5 */    {"IDoneSentence", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0xB6 */    {"IChooseVictoryDefeatText", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0xB7 */    {"IEnableViewCone", 0x01, { {0x04, "UNK"} }, "Enable view cone"},
    /* 0xB8 */    {"ISetPCAsUnwantedFor", 0x01, { {0x04, "UNK"} }, "SetPCAsUnwantedFor"},
    /* 0xB9 */    {"ISpecialAutorisation", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0xBA */    {"IRecordSpeakPC", 0x01, { {0x04, "UNK"} }, "Declare a speak PC sequence"},
    /* 0xBB */    {"ISelectPC", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0xBC */    {"ISetBuildingAsTrainWaggon", 0x01, { {0x04, "UNK"} }, "SetBuildingAsTrainWaggon"},
    /* 0xBD */    {"IRecordSeekActorCustomEvent", 0x01, { {0x04, "UNK"} }, "RecordSeekActorCustomEvent"},
    /* 0xBE */    {"IActivateDoorMouseSector", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0xBF */    {"IGetOutlineDisplay", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0xC0 */    {"ISetOutlineDisplay", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0xC1 */    {"ICustomizeMinimapDisplay", 0x01, { {0x04, "UNK"} }, "Customize minimap display"},
    /* 0xC2 */    {"IGetDoorStateForPC", 0x01, { {0x04, "UNK"} }, "Ask door state for PC"},
    /* 0xC3 */    {"IRecordLeaveGameDirectionnal", 0x01, { {0x04, "UNK"} }, "RecordLeaveGame"},
    /* 0xC4 */    {"ISetCorpseExistsInBuilding", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0xC5 */    {"IForceCheckVictory", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0xC6 */    {"IForceEmergencyBoxForMotionArea", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0xC7 */    {"ISetUserInputPossibleForHorse", 0x01, { {0x04, "UNK"} }, "Change user input to horse"},
};

//char *extern_func[NB_EXTERNAL_FUNC] = {"sub_5E2AF0", "sub_5E2B00", "sub_5E2B10", "sub_5E2B30",
//    "sub_5E2B40", "sub_5E2B50", "sub_5E2B70", "sub_5E2B80", "sub_5E2B90",
//    "sub_5E2BB0", "sub_5E2BC0", "sub_5E2BD0", "sub_5E2BE0", "sub_5E2BF0",
//    "sub_5E2C00", "sub_5E2C20", "sub_5E2C30", "sub_5E2C40", "sub_5E2C50",
//    "sub_5E2C60", "sub_5E2C70", "sub_5E2C80", "sub_5E2C90", "sub_5E2CA0",
//    "sub_5E2CB0", "sub_5E2CC0", "sub_5E2CD0", "sub_5E2CE0", "sub_5E2CF0",
//    "sub_5E2D00", "sub_5E2D10", "sub_5E2D20", "sub_5E2D30", "sub_5E2D40",
//    "sub_5E2D50", "sub_5E2D60", "sub_5E2D70", "sub_5E2D90", "sub_5E2DB0",
//    "sub_5E2DD0", "sub_5E2DE0", "sub_5E2DF0", "sub_5E2E00", "sub_5E2E10",
//    "sub_5E2E20", "sub_5E2E40", "sub_5E2E60", "sub_5E2E80", "sub_5E2E90",
//    "sub_5E2EB0", "sub_5E2EC0", "sub_5E2EE0", "sub_5E2EF0", "sub_5E2F10",
//    "sub_5E2F20", "sub_5E2F40", "sub_5E2F60", "sub_5E2F80", "sub_5E2FA0",
//    "sub_5E2FB0", "sub_5E2FD0", "sub_5E2FF0", "sub_5E3000", "sub_5E3010",
//    "sub_5E3020", "sub_5E3040", "sub_5E3050", "sub_5E3060", "sub_5E3070",
//    "sub_5E3090", "sub_5E30A0", "sub_5E30B0", "sub_5E30C0", "sub_5E30D0",
//    "sub_5E30E0", "sub_5E30F0", "sub_5E3100", "sub_5E3110", "sub_5E3120",
//    "sub_5E3130", "sub_5E3140", "sub_5E3150", "sub_5E3170", "sub_5E3180",
//    "sub_5E3190", "sub_5E31B0", "sub_5E31D0", "sub_5E31E0", "sub_5E31F0",
//    "sub_5E3200", "sub_5E3220", "sub_5E3240", "sub_5E3260", "sub_5E3280",
//    "sub_5E32A0", "sub_5E32C0", "sub_5E32E0", "sub_5E3300", "sub_5E3320",
//    "sub_5E3330", "sub_5E3340", "sub_5E3350", "sub_5E3360", "sub_5E3370",
//    "sub_5E3390", "sub_5E33A0", "sub_5E33C0", "sub_5E33E0", "sub_5E33F0",
//    "sub_5E3400", "sub_5E3410", "sub_5E3420", "sub_5E3430", "sub_5E3440",
//    "sub_5E3450", "sub_5E3460", "sub_5E3470", "sub_5E3480", "sub_5E3490",
//    "sub_5E34B0", "sub_5E34D0", "sub_5E34F0", "sub_5E3510", "sub_5E3530",
//    "sub_5E3540", "sub_5E3550", "sub_5E3570", "sub_5E3580", "sub_5E3590",
//    "sub_5E35A0", "sub_5E35B0", "sub_5E35C0", "sub_5E35E0", "sub_5E3600",
//    "sub_5E3620", "sub_5E3630", "sub_5E3640", "sub_5E3650", "sub_5E3660",
//    "sub_5E3680", "sub_5E36A0", "sub_5E36C0", "sub_5E36E0", "sub_5E36F0",
//    "sub_5E3700", "sub_5E3710", "sub_5E3720", "sub_5E3730", "sub_5E3740",
//    "sub_5E3750", "sub_5E3760", "sub_5E3770", "sub_5E3790", "sub_5E37B0",
//    "sub_5E37D0", "sub_5E37F0", "sub_5E3800", "sub_5E3820", "sub_5E3830",
//    "sub_5E3850", "sub_5E3860", "sub_5E3870", "sub_5E3890", "sub_5E38B0",
//    "sub_5E38D0", "sub_5E38F0", "sub_5E3900", "sub_5E3920", "sub_5E3930",
//    "sub_5E3940", "sub_5E3960", "sub_5E3970", "sub_5E3980", "sub_5E3990",
//    "sub_5E39A0", "sub_5E39C0", "sub_5E39E0", "sub_5E3A00", "sub_5E3A10",
//    "sub_5E3A20", "sub_5E3A40", "sub_5E3A50", "sub_5E3A60", "sub_5E3A70",
//    "sub_5E3A80", "sub_5E3A90", "sub_5E3AB0", "sub_5E3AD0", "sub_5E3AE0",
//    "sub_5E3AF0", "sub_5E3B20", "sub_5E3B40", "sub_5E3B50", "sub_5E3B60",
//    "sub_5E3B70", "sub_5E3B80", "sub_5E3BA0", "sub_5E3BB0", "sub_5E3BC0",
//    "sub_5E3BD0" };

void odv_scb_print_opcode_bytes(const unsigned char *buf)
{
    unsigned int i;

    for (i = 0; i < 10; i++) {
        printf("%02X ", buf[i]);
    }
}

/*
    /!\                                     /!\
    /!\ Those values are probably wrong     /!\
    /!\                                     /!\
*/
char *odv_scb_operation_flag_info(unsigned short flag)
{
    if (flag) {
        switch (flag) {
            case 0x4000:
                /* printf("f: 0x4000"); */
                return "class_var_";
                break;

            case 0x8000:
                /* printf("f: 0x8000 (NS_VOLATILE_VAR)"); */
                return "vol_var_";
                break;

            case 0xC000:
                /* return "f: 0xC000 (NS_TEMP_VAR)"; */
                return "tmp_var_";
                break;

            default:
                fprintf(stderr, "[-] unknow flag : %04X\n", flag);
                return "";
        }
    }
    else {
        /* printf("f: 0x0000"); */
        return "NULL";
    }
}

void odv_scb_diassemble(unsigned int addr, const unsigned char *buf)
{
    unsigned char opcode;
    unsigned short sval_0;
    unsigned short flag_0;
    unsigned short sval_1;
    unsigned short flag_1;
    unsigned short sval_2;
    unsigned short flag_2;
    unsigned int ival_0;
    float fval_0;
    char op_00[100];

    opcode = buf[0];
    printf("0x%08X: ", addr);
    odv_scb_print_opcode_bytes(buf);
    switch (opcode) {

        case 0x00:
            printf("    [!] Operation not allowed [!]\n");
            break;

        case 0x01:
            printf("    NOP\n");
            break;

        case 0x02:
            sval_0 = *(unsigned short*)(buf + 1);
            flag_0 = sval_0 & 0xC000;
            sval_0 = sval_0 & 0x3FFF;
            printf("    %-15s %s%d\n", "PARAM", odv_scb_operation_flag_info(flag_0), sval_0);
            break;

        case 0x03:
            sval_0 = *(unsigned short*)(buf + 1);
            sval_1 = *(unsigned short*)(buf + 1 + 2);
            printf("    InitFunction(SIZEOFVOLATILE=0x%04X, SIZEOFTEMPOR=0x%04X)\n", sval_0, sval_1);
            break;

        case 0x04:
            printf("    VMCore::EndFunction\n");
            break;

        case 0x05:
            ival_0 = *(unsigned int*)(buf + 1);
            printf("    %-15s 0x%08X\n", "CALL", ival_0);
            break;

        case 0x06:
            printf("    RETURN\n");
            break;

        case 0x07:
            sval_0 = *(unsigned short*)(buf + 1);
            flag_0 = sval_0 & 0xC000;
            sval_0 = sval_0 & 0x3FFF;
            printf("    %-15s %s%d\n", "RETURN", odv_scb_operation_flag_info(flag_0), sval_0);
            break;

        case 0x08:
            sval_0 = *(unsigned short*)(buf + 1);
            flag_0 = sval_0 & 0xC000;
            sval_0 = sval_0 & 0x3FFF;
            ival_0 = *(unsigned int*)(buf + 1 + 4);
            snprintf(op_00, sizeof (op_00), "%s%d", odv_scb_operation_flag_info(flag_0), sval_0);
            printf("    %-15s := GETPARAM %d", op_00, ival_0);
            printf("\n");
            break;

        case 0x09:
            sval_0 = *(unsigned short*)(buf + 1);
            flag_0 = sval_0 & 0xC000;
            sval_0 = sval_0 & 0x3FFF;
            ival_0 = *(unsigned int*)(buf + 1 + 4);
            printf("    SETPARAM %d %s%d", ival_0, odv_scb_operation_flag_info(flag_0), sval_0);
            printf("\n");
            break;

        case 0x0A:
            sval_0 = *(unsigned short*)(buf + 1);
            flag_0 = sval_0 & 0xC000;
            sval_0 = sval_0 & 0x3FFF;
            snprintf(op_00, sizeof (op_00), "%s%d", odv_scb_operation_flag_info(flag_0), sval_0);
            printf("    %-15s := GETRETURN", op_00);
            printf("\n");
            break;

        case 0x0B:
            sval_0 = *(unsigned short*)(buf + 1);
            flag_0 = sval_0 & 0xC000;
            sval_0 = sval_0 & 0x3FFF;
            printf("    %-15s %s%d", "NATIVEPARAM", odv_scb_operation_flag_info(flag_0), sval_0);
            printf("\n");
            break;

        case 0x0C:
            ival_0 = *(unsigned int*)(buf + 1);
            if (ival_0 >= NB_EXTERNAL_FUNC) {
                printf("    NATIVECALL - [-] Invalid external method num %d\n", ival_0);
                break;
            }
            printf("    %-15s [%02X] ; %s", "NATIVECALL", ival_0, extern_func[ival_0].name);
            /*
            for (unsigned int numarg = 0; numarg < extern_func[ival_0].nbarguments; numarg++) {
                if ((numarg + 1) != extern_func[ival_0].nbarguments) {
                    printf("(%s)ARG_%02X, ", extern_func[ival_0].funcargs[numarg].type, numarg);
                }
                else {
                    printf("(%s)ARG_%02X", extern_func[ival_0].funcargs[numarg].type, numarg);
                }
            }
            printf(") ; %s\n", extern_func[ival_0].description);
            */
            printf("\n");
            break;

        case 0x0D:
            sval_0 = *(unsigned short*)(buf + 1);
            flag_0 = sval_0 & 0xC000;
            sval_0 = sval_0 & 0x3FFF;
            snprintf(op_00, sizeof (op_00), "%s%d", odv_scb_operation_flag_info(flag_0), sval_0);
            printf("    %-15s := NATIVEGETRETURN\n", op_00);
            break;

        case 0x0E:
            ival_0 = *(unsigned int*)(buf + 1);
            printf("    %-15s 0x%08X\n", "GOTO", ival_0);
            break;

        case 0x0F:
            sval_0 = *(unsigned short*)(buf + 1);
            flag_0 = sval_0 & 0xC000;
            sval_0 = sval_0 & 0x3FFF;
            ival_0 = *(unsigned int*)(buf + 1 + 4);
            //snprintf(op_00, sizeof (op_00), "%s%d", odv_scb_operation_flag_info(flag_0), sval_0);
            //printf("    IF ( %-15s != 0 ) THEN GOTO %08X\n", op_00, ival_0);
            printf("    IF ( %s%d != 0 ) THEN GOTO 0x%08X\n", odv_scb_operation_flag_info(flag_0), sval_0, ival_0);
            break;

        case 0x10:
            sval_0 = *(unsigned short*)(buf + 1);
            flag_0 = sval_0 & 0xC000;
            sval_0 = sval_0 & 0x3FFF;
            ival_0 = *(unsigned int*)(buf + 1 + 4);
            //snprintf(op_00, sizeof (op_00), "%s%d", odv_scb_operation_flag_info(flag_0), sval_0);
            //printf("    IF ( %-15s == 0 ) THEN GOTO %08X\n", op_00, ival_0);
            printf("    IF ( %s%d == 0 ) THEN GOTO 0x%08X\n", odv_scb_operation_flag_info(flag_0), sval_0, ival_0);
            break;

        case 0x11:
            sval_0 = *(unsigned short*)(buf + 1);
            flag_0 = sval_0 & 0xC000;
            sval_0 = sval_0 & 0x3FFF;
            sval_1 = *(unsigned short*)(buf + 1 + 2);
            flag_1 = sval_1 & 0xC000;
            sval_1 = sval_1 & 0x3FFF;
            snprintf(op_00, sizeof (op_00), "%s%d", odv_scb_operation_flag_info(flag_0), sval_0);
            printf("    %-15s := %s%d\n", op_00, odv_scb_operation_flag_info(flag_1), sval_1);
            break;

        case 0x12:
            printf("    0x12 - TODO\n");
            exit(42);
            break;

        case 0x13:
            sval_0 = *(unsigned short*)(buf + 1);
            flag_0 = sval_0 & 0xC000;
            sval_0 = sval_0 & 0x3FFF;
            ival_0 = *(unsigned int*)(buf + 1 + 4);
            snprintf(op_00, sizeof (op_00), "%s%d", odv_scb_operation_flag_info(flag_0), sval_0);
            printf("    %-15s :=I 0x%08X\n", op_00, ival_0);
            break;


        case 0x14:
            sval_0 = *(unsigned short*)(buf + 1);
            flag_0 = sval_0 & 0xC000;
            sval_0 = sval_0 & 0x3FFF;
            fval_0 = *(float*)(buf + 1 + 4);
            snprintf(op_00, sizeof (op_00), "%s%d", odv_scb_operation_flag_info(flag_0), sval_0);
            printf("    %-15s :=F %f\n", op_00, fval_0);
            break;

        case 0x15:
            sval_0 = *(unsigned short*)(buf + 1);
            flag_0 = sval_0 & 0xC000;
            sval_0 = sval_0 & 0x3FFF;
            sval_1 = *(unsigned short*)(buf + 1 + 2);
            flag_1 = sval_1 & 0xC000;
            sval_1 = sval_1 & 0x3FFF;
            snprintf(op_00, sizeof (op_00), "%s%d", odv_scb_operation_flag_info(flag_0), sval_0);
            printf("    %-15s :=I - %s%d", op_00, odv_scb_operation_flag_info(flag_1), sval_1);
            printf("\n");
            break;

        case 0x16:
            sval_0 = *(unsigned short*)(buf + 1);
            flag_0 = sval_0 & 0xC000;
            sval_0 = sval_0 & 0x3FFF;
            sval_1 = *(unsigned short*)(buf + 1 + 2);
            flag_1 = sval_1 & 0xC000;
            sval_1 = sval_1 & 0x3FFF;
            snprintf(op_00, sizeof (op_00), "%s%d", odv_scb_operation_flag_info(flag_0), sval_0);
            printf("    %-15s :=F - %s%d", op_00, odv_scb_operation_flag_info(flag_1), sval_1);
            printf("\n");
            break;

        case 0x17:
            printf("    0x17 - TODO\n");
            exit(42);
            break;


        case 0x18:
            printf("    0x18 - TODO\n");
            exit(42);
            break;

        case 0x19:
        case 0x1A:
        case 0x1B:
        case 0x1C:
        {
            char *operator[4] = {"+I", "-I", "*I", "/I"};
            sval_0 = *(unsigned short*)(buf + 1);
            flag_0 = sval_0 & 0xC000;
            sval_0 = sval_0 & 0x3FFF;
            sval_1 = *(unsigned short*)(buf + 1 + 2);
            flag_1 = sval_1 & 0xC000;
            sval_1 = sval_1 & 0x3FFF;
            sval_2 = *(unsigned short*)(buf + 1 + 4);
            flag_2 = sval_2 & 0xC000;
            sval_2 = sval_2 & 0x3FFF;
            snprintf(op_00, sizeof (op_00), "%s%d", odv_scb_operation_flag_info(flag_0), sval_0);
            printf("    %-15s :=I (%s%d %s %s%d)", op_00, odv_scb_operation_flag_info(flag_1), sval_1, operator[opcode - 0x19], odv_scb_operation_flag_info(flag_2), sval_2);
            printf("\n");
            break;
        }
        case 0x1D:
        case 0x1E:
        case 0x1F:
        case 0x20:
        {
            char *operator[4] = {"+F", "-F", "*F", "/F"};
            sval_0 = *(unsigned short*)(buf + 1);
            flag_0 = sval_0 & 0xC000;
            sval_0 = sval_0 & 0x3FFF;
            sval_1 = *(unsigned short*)(buf + 1 + 2);
            flag_1 = sval_1 & 0xC000;
            sval_1 = sval_1 & 0x3FFF;
            sval_2 = *(unsigned short*)(buf + 1 + 4);
            flag_2 = sval_2 & 0xC000;
            sval_2 = sval_2 & 0x3FFF;
            snprintf(op_00, sizeof (op_00), "%s%d", odv_scb_operation_flag_info(flag_0), sval_0);
            printf("    %-15s :=F (%s%d %s %s%d)", op_00, odv_scb_operation_flag_info(flag_1), sval_1, operator[opcode - 0x1D], odv_scb_operation_flag_info(flag_2), sval_2);
            printf("\n");
            break;
        }
        case 0x21:
        case 0x22:
        case 0x23:
        case 0x24:
        case 0x25:
        case 0x26:
        {
            char *operator[6] = {"<=I", "<I", ">=I", ">I", "!=I", "==I"};
            sval_0 = *(unsigned short*)(buf + 1);
            flag_0 = sval_0 & 0xC000;
            sval_0 = sval_0 & 0x3FFF;
            sval_1 = *(unsigned short*)(buf + 1 + 2);
            flag_1 = sval_1 & 0xC000;
            sval_1 = sval_1 & 0x3FFF;
            sval_2 = *(unsigned short*)(buf + 1 + 4);
            flag_2 = sval_2 & 0xC000;
            sval_2 = sval_2 & 0x3FFF;
            snprintf(op_00, sizeof (op_00), "%s%d", odv_scb_operation_flag_info(flag_0), sval_0);
            printf("    %-15s :=I (%s%d %s %s%d)", op_00, odv_scb_operation_flag_info(flag_1), sval_1, operator[opcode - 0x21], odv_scb_operation_flag_info(flag_2), sval_2);
            printf("\n");
            break;
        }
        case 0x27:
        case 0x28:
        case 0x29:
        case 0x2A:
        case 0x2B:
        case 0x2C:
        {
            char *operator[6] = {"<=F", "<F", ">=F", ">F", "!=F", "==F"};
            sval_0 = *(unsigned short*)(buf + 1);
            flag_0 = sval_0 & 0xC000;
            sval_0 = sval_0 & 0x3FFF;
            sval_1 = *(unsigned short*)(buf + 1 + 2);
            flag_1 = sval_1 & 0xC000;
            sval_1 = sval_1 & 0x3FFF;
            sval_2 = *(unsigned short*)(buf + 1 + 4);
            flag_2 = sval_2 & 0xC000;
            sval_2 = sval_2 & 0x3FFF;
            snprintf(op_00, sizeof (op_00), "%s%d", odv_scb_operation_flag_info(flag_0), sval_0);
            printf("    %-15s :=I (%s%d %s %s%d)", op_00, odv_scb_operation_flag_info(flag_1), sval_1, operator[opcode - 0x27], odv_scb_operation_flag_info(flag_2), sval_2);
            printf("\n");
            break;
        }
        default:
            printf("    %02X - FUU - %08X %08X\n", opcode, *(unsigned int*)(buf + 1), *(unsigned int*)(buf + 1 + 4));
            exit(42);
    }
}