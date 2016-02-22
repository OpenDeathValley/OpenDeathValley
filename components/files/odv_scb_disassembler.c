#include "odv_scb_disassembler.h"

struct ODVExternalFunction extern_func[NB_EXTERNAL_FUNC] = {
    /* 0x00 */    {"sub_5E2AF0", 0x01, { {0x04, "ID_DIALOGUE"} }, "Play a dialogue"},
    /* 0x01 */    {"sub_5E2B00", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x02 */    {"sub_5E2B10", 0x02, { {0x04, "UNK"}, {0x04, "UNK"} }, "UNK"},
    /* 0x03 */    {"sub_5E2B30", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x04 */    {"sub_5E2B40", 0x01, { {0x04, "FLOAT"} }, "Change zoom level"},
    /* 0x05 */    {"sub_5E2B50", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x06 */    {"sub_5E2B70", 0x01, { {0x04, "UNK"} }, "Output text on surface"},
    /* 0x07 */    {"sub_5E2B80", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x08 */    {"sub_5E2B90", 0x02, { {0x04, "UNK"}, {0x04, "UNK"} }, "Compare two values"},
    /* 0x09 */    {"sub_5E2BB0", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x0A */    {"sub_5E2BC0", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x0B */    {"sub_5E2BD0", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x0C */    {"sub_5E2BE0", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x0D */    {"sub_5E2BF0", 0x01, { {0x04, "UNK"} }, "Freeze actor element"},
    /* 0x0E */    {"sub_5E2C00", 0x03, { {0x04, "UNK"} , {0x04, "UNK"}, {0x04, "UNK"}}, "Inflict pain to actor"},
    /* 0x0F */    {"sub_5E2C20", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x10 */    {"sub_5E2C30", 0x01, { {0x04, "ACTOR_ID"} }, "Acces an actor by ID"},
    /* 0x11 */    {"sub_5E2C40", 0x01, { {0x04, "LOCATION_ID"} }, "Acces a location by ID"},
    /* 0x12 */    {"sub_5E2C50", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x13 */    {"sub_5E2C60", 0x01, { {0x04, "ACTOR"} }, "Test an actor element (flags & 0x03 == 0x01)"},
    /* 0x14 */    {"sub_5E2C70", 0x01, { {0x04, "ACTOR"} }, "Test an actor element (flags & 0x03 == 0x03)"},
    /* 0x15 */    {"sub_5E2C80", 0x01, { {0x04, "ACTOR"} }, "Test an actor element (flags & 0x0F == 0x0F)"},
    /* 0x16 */    {"sub_5E2C90", 0x01, { {0x04, "ACTOR"} }, "Test an actor element (flags & 0x0F == 0x07)"},
    /* 0x17 */    {"sub_5E2CA0", 0x01, { {0x04, "ACTOR"} }, "Test an actor element (flags & 0x1F == 0x17)"},
    /* 0x18 */    {"sub_5E2CB0", 0x01, { {0x04, "ACTOR"} }, "Test an actor element (flags & 0x1F == 0x07)"},
    /* 0x19 */    {"sub_5E2CC0", 0x01, { {0x04, "ACTOR"} }, "Test an actor element (flags & 0x07 == 0x03)"},
    /* 0x1A */    {"sub_5E2CD0", 0x01, { {0x04, "UNK"} }, "Test if NULL"},
    /* 0x1B */    {"sub_5E2CE0", 0x01, { {0x04, "ACTOR"} }, "Get the posture of a human actor"},
    /* 0x1C */    {"sub_5E2CF0", 0x01, { {0x04, "ACTOR"}, {0x04, "POSTURE"} }, "Set the posture of a human actor"},
    /* 0x1D */    {"sub_5E2D00", 0x00, { 0x00 }, "Get Cooper"},
    /* 0x1E */    {"sub_5E2D10", 0x00, { 0x00 }, "Get Sam"},
    /* 0x1F */    {"sub_5E2D20", 0x00, { 0x00 }, "Get Doc"},
    /* 0x20 */    {"sub_5E2D30", 0x00, { 0x00 }, "Get Kate"},
    /* 0x21 */    {"sub_5E2D40", 0x00, { 0x00 }, "Get Sanchez"},
    /* 0x22 */    {"sub_5E2D50", 0x00, { 0x00 }, "Get Mia"},
    /* 0x23 */    {"sub_5E2D60", 0x01, { {0x04, "ACTOR"} }, "Get location information"},
    /* 0x24 */    {"sub_5E2D70", 0x02, { {0x04, "ACTOR"}, {0x04, "UNK"} }, "Set location"},
    /* 0x25 */    {"sub_5E2D90", 0x02, { {0x04, "ACTOR"}, {0x04, "UNK"} }, "Check if a character is inside a location (must be a sector)"},
    /* 0x26 */    {"sub_5E2DB0", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x27 */    {"sub_5E2DD0", 0x01, { {0x04, "UNK"} }, "Check if any character is inside a location (must be a sector)"},
    /* 0x28 */    {"sub_5E2DE0", 0x01, { {0x04, "ACTOR"} }, "Switch profile"},
    /* 0x29 */    {"sub_5E2DF0", 0x01, { {0x04, "ACTOR"} }, "Get the movement style of an actor"},
    /* 0x2A */    {"sub_5E2E00", 0x01, { {0x04, "ACTOR"} }, "Desactivate an actor"},
    /* 0x2B */    {"sub_5E2E10", 0x01, { {0x04, "ACTOR"} }, "Activate an actor"},
    /* 0x2C */    {"sub_5E2E20", 0x03, { {0x04, "ACTOR"}, {0x04, "ACTION"}, {0x04, "AVAILABILITY"} }, "Set the availability of an action of an actor"},
    /* 0x2D */    {"sub_5E2E40", 0x02, { {0x04, "ACTOR"}, {0x04, "AVAILABILITY"} }, "Set the availability of an actor"},
    /* 0x2E */    {"sub_5E2E60", 0x03, { {0x04, "ACTOR"}, {0x04, "PROPERTY"}, {0x04, "NUMBER"} }, "Set the property of an actor"},
    /* 0x2F */    {"sub_5E2E80", 0x02, { {0x04, "ACTOR"}, {0x04, "PROPERTY"} }, "Get the property of an actor"},
    /* 0x30 */    {"sub_5E2E90", 0x02, { {0x04, "ACTOR"}, {0x04, "ALERT_STATE"}  }, "Set alert state of a NPC"},
    /* 0x31 */    {"sub_5E2EB0", 0x01, { {0x04, "ACTOR"} }, "Get alert state of a NPC"},
    /* 0x32 */    {"sub_5E2EC0", 0x02, { {0x04, "ACTOR"}, {0x04, "AI_STATE"} }, "Set AI state"},
    /* 0x33 */    {"sub_5E2EE0", 0x01, { {0x04, "ACTOR"} }, "Get AI state"},
    /* 0x34 */    {"sub_5E2EF0", 0x02, { {0x04, "ACTOR"}, {0x04, "ATTITUDE"} }, "Set attitude of an NPC"},
    /* 0x35 */    {"sub_5E2F10", 0x01, { {0x04, "ACTOR"} }, "Get attitude of an NPC"},
    /* 0x36 */    {"sub_5E2F20", 0x03, { {0x04, "ACTOR"}, {0x04, "UNK"}, {0x04, "UNK"} }, "Set AI level of an NPC"},
    /* 0x37 */    {"sub_5E2F40", 0x02, { {0x04, "ACTOR"}, {0x04, "UNK"} }, "Set viewcone of an NPC"},
    /* 0x38 */    {"sub_5E2F60", 0x03, { {0x04, "ACTOR"},  {0x04, "UNK"},  {0x04, "UNK"} }, "Get stare actor command"},
    /* 0x39 */    {"sub_5E2F80", 0x03, { {0x04, "ACTOR"},  {0x04, "UNK"},  {0x04, "UNK"} }, "Get stare location command"},
    /* 0x3A */    {"sub_5E2FA0", 0x02, { {0x04, "ACTOR"} , {0x04, "UNK"} }, "Set patrol path for NPC"},
    /* 0x3B */    {"sub_5E2FB0", 0x03, { {0x04, "ACTOR"},  {0x04, "UNK"},  {0x04, "UNK"} }, "Set post for NPC"},
    /* 0x3C */    {"sub_5E2FD0", 0x02, { {0x04, "ACTOR"}, {0x04, "UNK"} }, "Lock AI"},
    /* 0x3D */    {"sub_5E2FF0", 0x01, { {0x04, "ACTOR"} }, "Unlock AI"},
    /* 0x3E */    {"sub_5E3000", 0x02, { {0x04, "ACTOR"} , {0x04, "UNK"} }, "Set battle decision"},
    /* 0x3F */    {"sub_5E3010", 0x02, { {0x04, "UNK"}, {0x04, "UNK"}}, "Set Noise"},
    /* 0x40 */    {"sub_5E3020", 0x02, { {0x04, "UNK"}, {0x04, "UNK"} }, "Freeze actor element"},
    /* 0x41 */    {"sub_5E3040", 0x01, { {0x04, "UNK"} }, "Get rider"},
    /* 0x42 */    {"sub_5E3050", 0x01, { {0x04, "UNK"} }, "Get horse"},
    /* 0x43 */    {"sub_5E3060", 0x01, { {0x04, "UNK"} }, "IsAnimationActive"},
    /* 0x44 */    {"sub_5E3070", 0x02, { {0x04, "ACTOR"}, {0x04, "UNK"} }, "SetAnimationState"},
    /* 0x45 */    {"sub_5E3090", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x46 */    {"sub_5E30A0", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x47 */    {"sub_5E30B0", 0x01, { {0x04, "UNK"} }, "IsHorseUsed"},
    /* 0x48 */    {"sub_5E30C0", 0x00, { 0x00 }, "UNK"},
    /* 0x49 */    {"sub_5E30D0", 0x01, { {0x04, "UNK"} }, "Launch sequence"},
    /* 0x4A */    {"sub_5E30E0", 0x00, { 0x00 }, "Increment sequence level"},
    /* 0x4B */    {"sub_5E30F0", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x4C */    {"sub_5E3100", 0x01, { {0x04, "UNK"} }, "Launch sequence (2)"},
    /* 0x4D */    {"sub_5E3110", 0x00, { 0x00 }, "Increment sequence level (2)"},
    /* 0x4E */    {"sub_5E3120", 0x01, { {0x04, "UNK"} }, "Declare fire sequence"},
    /* 0x4F */    {"sub_5E3130", 0x01, { {0x04, "UNK"} }, "Declare fire sequence (2)"},
    /* 0x50 */    {"sub_5E3140", 0x01, { {0x04, "UNK"} }, "Declare fire sequence (3)"},
    /* 0x51 */    {"sub_5E3150", 0x01, { {0x04, "UNK"} }, "Declare fire sequence (4)"},
    /* 0x52 */    {"sub_5E3170", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x53 */    {"sub_5E3180", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x54 */    {"sub_5E3190", 0x03, { {0x04, "UNK"}, {0x04, "UNK"}, {0x04, "UNK"} }, "Create a action available sequence with a actor"},
    /* 0x55 */    {"sub_5E31B0", 0x02, { {0x04, "UNK"}, {0x04, "UNK"} }, "Create a action available sequence with a actor"},
    /* 0x56 */    {"sub_5E31D0", 0x01, { {0x04, "UNK"} }, "Create a move sequence with a actor"},
    /* 0x57 */    {"sub_5E31E0", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x58 */    {"sub_5E31F0", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x59 */    {"sub_5E3200", 0x03, { {0x04, "UNK"}, {0x04, "UNK"}, {0x04, "UNK"} }, "Create move sequence"},
    /* 0x5A */    {"sub_5E3220", 0x03, { {0x04, "UNK"}, {0x04, "UNK"}, {0x04, "UNK"} }, "Create move sequence (2)"},
    /* 0x5B */    {"sub_5E3240", 0x02, { {0x04, "UNK"}, {0x04, "UNK"} }, "Create a turn sequence"},
    /* 0x5C */    {"sub_5E3260", 0x02, { {0x04, "UNK"}, {0x04, "UNK"} }, "Create a mount sequence"},
    /* 0x5D */    {"sub_5E3280", 0x02, { {0x04, "UNK"}, {0x04, "UNK"} }, "Create a dismount sequence"},
    /* 0x5E */    {"sub_5E32A0", 0x02, { {0x04, "UNK"}, {0x04, "UNK"} }, "Create a fire sequence"},
    /* 0x5F */    {"sub_5E32C0", 0x02, { {0x04, "UNK"}, {0x04, "UNK"} }, "Create anim sequence"},
    /* 0x60 */    {"sub_5E32E0", 0x02, { {0x04, "UNK"}, {0x04, "UNK"} }, "Play anim sequence"},
    /* 0x61 */    {"sub_5E3300", 0x02, { {0x04, "UNK"}, {0x04, "UNK"} }, "Declare play anim sequence"},
    /* 0x62 */    {"sub_5E3320", 0x01, { {0x04, "UNK"} }, "Lock AI method"},
    /* 0x63 */    {"sub_5E3330", 0x01, { {0x04, "UNK"} }, "Unlock AI method"},
    /* 0x64 */    {"sub_5E3340", 0x00, { 0x00 }, "Declare a fire at sequence"},
    /* 0x65 */    {"sub_5E3350", 0x01, { {0x04, "UNK"} }, "Declare a fire at sequence (2)"},
    /* 0x66 */    {"sub_5E3360", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x67 */    {"sub_5E3370", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x68 */    {"sub_5E3390", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x69 */    {"sub_5E33A0", 0x01, { {0x04, "UNK"} }, "DO NOTHING"},
    /* 0x6A */    {"sub_5E33C0", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x6B */    {"sub_5E33E0", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x6C */    {"sub_5E33F0", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x6D */    {"sub_5E3400", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x6E */    {"sub_5E3410", 0x00, { 0x00 }, "Stop channel"},
    /* 0x6F */    {"sub_5E3420", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x70 */    {"sub_5E3430", 0x01, { {0x04, "UNK"} }, "Get sound source"},
    /* 0x71 */    {"sub_5E3440", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x72 */    {"sub_5E3450", 0x01, { {0x04, "UNK"} }, "Stop Channel (2)"},
    /* 0x73 */    {"sub_5E3460", 0x01, { {0x04, "UNK"} }, "Stop Channel (3)"},
    /* 0x74 */    {"sub_5E3470", 0x01, { {0x04, "UNK"} }, "Clean actor"},
    /* 0x75 */    {"sub_5E3480", 0x01, { {0x04, "UNK"} }, "Add actor to a building"},
    /* 0x76 */    {"sub_5E3490", 0x01, { {0x04, "UNK"} }, "Clean actor (2)"},
    /* 0x77 */    {"sub_5E34B0", 0x01, { {0x04, "UNK"} }, "Add actor to a script zone"},
    /* 0x78 */    {"sub_5E34D0", 0x01, { {0x04, "UNK"} }, "Open a door"},
    /* 0x79 */    {"sub_5E34F0", 0x01, { {0x04, "UNK"} }, "Open a door (2)"},
    /* 0x7A */    {"sub_5E3510", 0x01, { {0x04, "UNK"} }, "Open a door (3)"},
    /* 0x7B */    {"sub_5E3530", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x7C */    {"sub_5E3540", 0x01, { {0x04, "UNK"} }, "Get direction of a actor"},
    /* 0x7D */    {"sub_5E3550", 0x01, { {0x04, "UNK"} }, "Set direction of a actor"},
    /* 0x7E */    {"sub_5E3570", 0x01, { {0x04, "UNK"} }, "Stop a actor"},
    /* 0x7F */    {"sub_5E3580", 0x01, { {0x04, "UNK"} }, "GetDistance"},
    /* 0x80 */    {"sub_5E3590", 0x01, { {0x04, "UNK"} }, "GetAction"},
    /* 0x81 */    {"sub_5E35A0", 0x01, { {0x04, "UNK"} }, "Test actor element (flag & 0x03) == 0x02"},
    /* 0x82 */    {"sub_5E35B0", 0x01, { {0x04, "UNK"} }, "Set path walking style"},
    /* 0x83 */    {"sub_5E35C0", 0x01, { {0x04, "UNK"} }, "Create a replace-anim sequence"},
    /* 0x84 */    {"sub_5E35E0", 0x01, { {0x04, "UNK"} }, "Create a restore-anim sequence"},
    /* 0x85 */    {"sub_5E3600", 0x01, { {0x04, "UNK"} }, "Test if a NPC see ACTOR"},
    /* 0x86 */    {"sub_5E3620", 0x01, { {0x04, "UNK"} }, "Get index actor element"},
    /* 0x87 */    {"sub_5E3630", 0x01, { {0x04, "UNK"} }, "JoinArmy"},
    /* 0x88 */    {"sub_5E3640", 0x01, { {0x04, "UNK"} }, "DeclareWar"},
    /* 0x89 */    {"sub_5E3650", 0x01, { {0x04, "UNK"} }, "GetArmy"},
    /* 0x8A */    {"sub_5E3660", 0x01, { {0x04, "UNK"} }, "SetSoldierSeesSoldier"},
    /* 0x8B */    {"sub_5E3680", 0x01, { {0x04, "UNK"} }, "SetSoldierSeesArmy"},
    /* 0x8C */    {"sub_5E36A0", 0x01, { {0x04, "UNK"} }, "SetArmySeesSoldier"},
    /* 0x8D */    {"sub_5E36C0", 0x01, { {0x04, "UNK"} }, "SetArmySeesArmy"},
    /* 0x8E */    {"sub_5E36E0", 0x01, { {0x04, "UNK"} }, "GetNumberOfVisibleSoldiers"},
    /* 0x8F */    {"sub_5E36F0", 0x01, { {0x04, "UNK"} }, "GetVisibleSoldier"},
    /* 0x90 */    {"sub_5E3700", 0x01, { {0x04, "UNK"} }, "GetNearestVisibleSoldier"},
    /* 0x91 */    {"sub_5E3710", 0x01, { {0x04, "UNK"} }, "CreateListOfRecentlySeenSoldiers"},
    /* 0x92 */    {"sub_5E3720", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x93 */    {"sub_5E3730", 0x01, { {0x04, "UNK"} }, "GetRecentlySeenSoldier"},
    /* 0x94 */    {"sub_5E3740", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x95 */    {"sub_5E3750", 0x01, { {0x04, "UNK"} }, "PutSnakeOnMap"},
    /* 0x96 */    {"sub_5E3760", 0x01, { {0x04, "UNK"} }, "PutWatchOnMap"},
    /* 0x97 */    {"sub_5E3770", 0x01, { {0x04, "UNK"} }, "RecordTakeCorpse"},
    /* 0x98 */    {"sub_5E3790", 0x01, { {0x04, "UNK"} }, "Walk into a building"},
    /* 0x99 */    {"sub_5E37B0", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x9A */    {"sub_5E37D0", 0x01, { {0x04, "UNK"} }, "RecordEnterBarrel"},
    /* 0x9B */    {"sub_5E37F0", 0x01, { {0x04, "UNK"} }, "RecordLeaveBarrel"},
    /* 0x9C */    {"sub_5E3800", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x9D */    {"sub_5E3820", 0x01, { {0x04, "UNK"} }, "RecordLeaveCorpse"},
    /* 0x9E */    {"sub_5E3830", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0x9F */    {"sub_5E3850", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0xA0 */    {"sub_5E3860", 0x01, { {0x04, "UNK"} }, "SetAnimationState"},
    /* 0xA1 */    {"sub_5E3870", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0xA2 */    {"sub_5E3890", 0x01, { {0x04, "UNK"} }, "EnableHorseUseFor"},
    /* 0xA3 */    {"sub_5E38B0", 0x01, { {0x04, "UNK"} }, "Define animal alert"},
    /* 0xA4 */    {"sub_5E38D0", 0x01, { {0x04, "UNK"} }, "RecordTieCorpse"},
    /* 0xA5 */    {"sub_5E38F0", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0xA6 */    {"sub_5E3900", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0xA7 */    {"sub_5E3920", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0xA8 */    {"sub_5E3930", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0xA9 */    {"sub_5E3940", 0x01, { {0x04, "UNK"} }, "Make a door doclockpickable"},
    /* 0xAA */    {"sub_5E3960", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0xAB */    {"sub_5E3970", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0xAC */    {"sub_5E3980", 0x01, { {0x04, "UNK"} }, "PutActorInBarrel"},
    /* 0xAD */    {"sub_5E3990", 0x01, { {0x04, "UNK"} }, "Skip data ???"},
    /* 0xAE */    {"sub_5E39A0", 0x01, { {0x04, "UNK"} }, "Forbid a horse"},
    /* 0xAF */    {"sub_5E39C0", 0x01, { {0x04, "UNK"} }, "Declare a speak sequence"},
    /* 0xB0 */    {"sub_5E39E0", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0xB1 */    {"sub_5E3A00", 0x01, { {0x04, "UNK"} }, "Get a random value"},
    /* 0xB2 */    {"sub_5E3A10", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0xB3 */    {"sub_5E3A20", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0xB4 */    {"sub_5E3A40", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0xB5 */    {"sub_5E3A50", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0xB6 */    {"sub_5E3A60", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0xB7 */    {"sub_5E3A70", 0x01, { {0x04, "UNK"} }, "Enable view cone"},
    /* 0xB8 */    {"sub_5E3A80", 0x01, { {0x04, "UNK"} }, "SetPCAsUnwantedFor"},
    /* 0xB9 */    {"sub_5E3A90", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0xBA */    {"sub_5E3AB0", 0x01, { {0x04, "UNK"} }, "Declare a speak PC sequence"},
    /* 0xBB */    {"sub_5E3AD0", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0xBC */    {"sub_5E3AE0", 0x01, { {0x04, "UNK"} }, "SetBuildingAsTrainWaggon"},
    /* 0xBD */    {"sub_5E3AF0", 0x01, { {0x04, "UNK"} }, "RecordSeekActorCustomEvent"},
    /* 0xBE */    {"sub_5E3B20", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0xBF */    {"sub_5E3B40", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0xC0 */    {"sub_5E3B50", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0xC1 */    {"sub_5E3B60", 0x01, { {0x04, "UNK"} }, "Customize minimap display"},
    /* 0xC2 */    {"sub_5E3B70", 0x01, { {0x04, "UNK"} }, "Ask door state for PC"},
    /* 0xC3 */    {"sub_5E3B80", 0x01, { {0x04, "UNK"} }, "RecordLeaveGame"},
    /* 0xC4 */    {"sub_5E3BA0", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0xC5 */    {"sub_5E3BB0", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0xC6 */    {"sub_5E3BC0", 0x01, { {0x04, "UNK"} }, "UNK"},
    /* 0xC7 */    {"sub_5E3BD0", 0x01, { {0x04, "UNK"} }, "Change user input to horse"},
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
        return "f: 0x0000";
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
    unsigned int numarg;

    opcode = buf[0];
    printf("%08X: ", addr);
    odv_scb_print_opcode_bytes(buf);
    switch (opcode) {

        case 0x00:
            printf("    0x00 - Operation not allowed\n");
            break;

        case 0x01:
            printf("    0x01 - NOP\n");
            break;

        case 0x02:
            sval_0 = *(unsigned short*)(buf + 1);
            flag_0 = sval_0 & 0xC000;
            sval_0 = sval_0 & 0x3FFF;
            printf("    0x02 - sval_0: 0x%04X ; ", sval_0);
            odv_scb_operation_flag_info(flag_0);
            printf("\n");
            break;

        case 0x03:
            sval_0 = *(unsigned short*)(buf + 1);
            sval_1 = *(unsigned short*)(buf + 1 + 2);
            /* printf("    0x03 - sval_0 (SIZEOFVOLATILE): 0x%04X ; sval_1 (SIZEOFTEMPOR): 0x%04X\n", sval_0, sval_1); */
            printf("    0x03 - InitFunction(SIZEOFVOLATILE=0x%04X, SIZEOFTEMPOR=0x%04X)\n", sval_0, sval_1);
            break;

        case 0x04:
            printf("    0x04 - VMCore::EndFunction\n");
            break;

        case 0x07:
            sval_0 = *(unsigned short*)(buf + 1);
            flag_0 = sval_0 & 0xC000;
            sval_0 = sval_0 & 0x3FFF;
            /* printf("    0x07 - ??? - sval_0: 0x%04X ; ", sval_0);
            odv_scb_operation_flag_info(flag_0); */
            printf("    0x07 - return %s%d", odv_scb_operation_flag_info(flag_0), sval_0);
            printf("\n");
            break;

        case 0x08:
            sval_0 = *(unsigned short*)(buf + 1);
            flag_0 = sval_0 & 0xC000;
            sval_0 = sval_0 & 0x3FFF;
            ival_0 = *(unsigned int*)(buf + 1 + 4);
            /* printf("    0x08 - sval_0: 0x%04X ; ", sval_0);
            odv_scb_operation_flag_info(flag_0);
            printf(" ; ival_0: 0x%08X", ival_0); */
            printf("    0x08 - mov %s%d, somewhere_%d", odv_scb_operation_flag_info(flag_0), sval_0, ival_0);
            printf("\n");
            break;

        case 0x0B:
            sval_0 = *(unsigned short*)(buf + 1);
            flag_0 = sval_0 & 0xC000;
            sval_0 = sval_0 & 0x3FFF;
            /* printf("    0x0B - PUSH ARGS - sval_0: 0x%04X ; ", sval_0);
            odv_scb_operation_flag_info(flag_0); */
            printf("    0x0B - push %s%d", odv_scb_operation_flag_info(flag_0), sval_0);
            printf("\n");
            break;

        case 0x0C:
            ival_0 = *(unsigned int*)(buf + 1);
            if (ival_0 >= NB_EXTERNAL_FUNC) {
                printf("    0x0C - [-] Invalid external method num %d\n", ival_0);
                break;
            }
            printf("    0x0C - call [%02X]        %s(", ival_0, extern_func[ival_0].name);
            for (numarg = 0; numarg < extern_func[ival_0].nbarguments; numarg++) {
                if ((numarg + 1) != extern_func[ival_0].nbarguments) {
                    printf("(%s)ARG_%02X, ", extern_func[ival_0].funcargs[numarg].type, numarg);
                }
                else {
                    printf("(%s)ARG_%02X", extern_func[ival_0].funcargs[numarg].type, numarg);
                }
            }
            printf(") ; %s\n", extern_func[ival_0].description);
            break;

        case 0x0D:
            sval_0 = *(unsigned short*)(buf + 1);
            flag_0 = sval_0 & 0xC000;
            sval_0 = sval_0 & 0x3FFF;
            /* printf("    0x0D - STORE RESULT - sval_0: 0x%04X ; flag_0: 0x%4X\n", sval_0, flag_0); */
            printf("    0x0D - mov %s%d, RESULT", odv_scb_operation_flag_info(flag_0), sval_0);
            printf("\n");
            break;

        case 0x0E:
            ival_0 = *(unsigned int*)(buf + 1);
            printf("    0x0E - jmp %08X\n", ival_0);
            break;

        case 0x0F:
            sval_0 = *(unsigned short*)(buf + 1);
            flag_0 = sval_0 & 0xC000;
            sval_0 = sval_0 & 0x3FFF;
            ival_0 = *(unsigned int*)(buf + 1 + 4);
            /* printf("    0x0F - JE - sval_0: 0x%04X ; flag_0: 0x%4X ; ival_0: 0x%08X\n", sval_0, flag_0, ival_0); */
            printf("    0x0F - test %s%d ; jz %08X", odv_scb_operation_flag_info(flag_0), sval_0, ival_0);
            printf("\n");
            break;

        case 0x11:
            sval_0 = *(unsigned short*)(buf + 1);
            flag_0 = sval_0 & 0xC000;
            sval_0 = sval_0 & 0x3FFF;
            sval_1 = *(unsigned short*)(buf + 1 + 2);
            flag_1 = sval_1 & 0xC000;
            sval_1 = sval_1 & 0x3FFF;
            /*printf("    0x11 - ??? - sval_0: 0x%04X ; ", sval_0);
            odv_scb_operation_flag_info(flag_0);
            printf(" ; sval_1: 0x%04X ; ", sval_1);
            odv_scb_operation_flag_info(flag_1);*/
            printf("    0x11 - mov %s%d, %s%d", odv_scb_operation_flag_info(flag_0), sval_0, odv_scb_operation_flag_info(flag_1), sval_1);
            printf("\n");
            break;

        case 0x13:
            sval_0 = *(unsigned short*)(buf + 1);
            flag_0 = sval_0 & 0xC000;
            sval_0 = sval_0 & 0x3FFF;
            ival_0 = *(unsigned int*)(buf + 1 + 4);
            /* printf("    0x13 - LOAD IMM32 - sval_0: 0x%04X ; ", sval_0);
            odv_scb_operation_flag_info(flag_0);
            printf(" ; ival_0: 0x%08X", ival_0); */
            printf("    0x13 - mov %s%d, 0x%08X", odv_scb_operation_flag_info(flag_0), sval_0, ival_0);
            printf("\n");
            break;

        case 0x14:
            sval_0 = *(unsigned short*)(buf + 1);
            flag_0 = sval_0 & 0xC000;
            sval_0 = sval_0 & 0x3FFF;
            ival_0 = *(unsigned int*)(buf + 1 + 4);
            /* printf("    0x14 - LOAD IMM32 - sval_0: 0x%04X ; ", sval_0);
            odv_scb_operation_flag_info(flag_0);
            printf(" ; ival_0: 0x%08X", ival_0); */
            printf("    0x14 - mov %s%d, 0x%08X", odv_scb_operation_flag_info(flag_0), sval_0, ival_0);
            printf("\n");
            break;

        case 0x15:
            sval_0 = *(unsigned short*)(buf + 1);
            flag_0 = sval_0 & 0xC000;
            sval_0 = sval_0 & 0x3FFF;
            sval_1 = *(unsigned short*)(buf + 1 + 2);
            flag_1 = sval_1 & 0xC000;
            sval_1 = sval_1 & 0x3FFF;
            /* printf("    0x15 - NS SUB - sval_0: 0x%04X ; ", sval_0);
            odv_scb_operation_flag_info(flag_0);
            printf(" ; sval_1: 0x%04X ; ", sval_1);
            odv_scb_operation_flag_info(flag_1); */
            printf("    0x13 - mov %s%d, -(%s%d)", odv_scb_operation_flag_info(flag_0), sval_0, odv_scb_operation_flag_info(flag_1), sval_1);
            printf("\n");
            break;

        case 0x19:
            sval_0 = *(unsigned short*)(buf + 1);
            flag_0 = sval_0 & 0xC000;
            sval_0 = sval_0 & 0x3FFF;
            sval_1 = *(unsigned short*)(buf + 1 + 2);
            flag_1 = sval_1 & 0xC000;
            sval_1 = sval_1 & 0x3FFF;
            sval_2 = *(unsigned short*)(buf + 1 + 4);
            flag_2 = sval_2 & 0xC000;
            sval_2 = sval_2 & 0x3FFF;
            printf("    0x24 - mov %s%d, (%s%d + %s%d)", odv_scb_operation_flag_info(flag_0), sval_0, odv_scb_operation_flag_info(flag_1), sval_1, odv_scb_operation_flag_info(flag_2), sval_2);
            printf("\n");
            break;

        case 0x1A:
            sval_0 = *(unsigned short*)(buf + 1);
            flag_0 = sval_0 & 0xC000;
            sval_0 = sval_0 & 0x3FFF;
            sval_1 = *(unsigned short*)(buf + 1 + 2);
            flag_1 = sval_1 & 0xC000;
            sval_1 = sval_1 & 0x3FFF;
            sval_2 = *(unsigned short*)(buf + 1 + 4);
            flag_2 = sval_2 & 0xC000;
            sval_2 = sval_2 & 0x3FFF;
            /* printf("    0x1A - SUB DWORD - sval_0: 0x%04X ; ", sval_0);
            odv_scb_operation_flag_info(flag_0);
            printf(" ; sval_1: 0x%04X ; ", sval_1);
            odv_scb_operation_flag_info(flag_1);
            printf(" ; sval_2: 0x%04X ; ", sval_2);
            odv_scb_operation_flag_info(flag_2); */
            printf("    0x24 - mov %s%d, (%s%d - %s%d)", odv_scb_operation_flag_info(flag_0), sval_0, odv_scb_operation_flag_info(flag_1), sval_1, odv_scb_operation_flag_info(flag_2), sval_2);
            printf("\n");
            break;

        case 0x23:
            sval_0 = *(unsigned short*)(buf + 1);
            flag_0 = sval_0 & 0xC000;
            sval_0 = sval_0 & 0x3FFF;
            sval_1 = *(unsigned short*)(buf + 1 + 2);
            flag_1 = sval_1 & 0xC000;
            sval_1 = sval_1 & 0x3FFF;
            sval_2 = *(unsigned short*)(buf + 1 + 4);
            flag_2 = sval_2 & 0xC000;
            sval_2 = sval_2 & 0x3FFF;
            printf("    0x23 - mov %s%d, (%s%d >= %s%d)", odv_scb_operation_flag_info(flag_0), sval_0, odv_scb_operation_flag_info(flag_1), sval_1, odv_scb_operation_flag_info(flag_2), sval_2);
            printf("\n");
            break;

        case 0x24:
            sval_0 = *(unsigned short*)(buf + 1);
            flag_0 = sval_0 & 0xC000;
            sval_0 = sval_0 & 0x3FFF;
            sval_1 = *(unsigned short*)(buf + 1 + 2);
            flag_1 = sval_1 & 0xC000;
            sval_1 = sval_1 & 0x3FFF;
            sval_2 = *(unsigned short*)(buf + 1 + 4);
            flag_2 = sval_2 & 0xC000;
            sval_2 = sval_2 & 0x3FFF;
            /* printf("    0x24 - GT DWORD - sval_0: 0x%04X ; ", sval_0);
            odv_scb_operation_flag_info(flag_0);
            printf(" ; sval_1: 0x%04X ; ", sval_1);
            odv_scb_operation_flag_info(flag_1);
            printf(" ; sval_2: 0x%04X ; ", sval_2);
            odv_scb_operation_flag_info(flag_2); */
            printf("    0x24 - mov %s%d, (%s%d > %s%d)", odv_scb_operation_flag_info(flag_0), sval_0, odv_scb_operation_flag_info(flag_1), sval_1, odv_scb_operation_flag_info(flag_2), sval_2);
            printf("\n");
            break;

        case 0x25:
            sval_0 = *(unsigned short*)(buf + 1);
            flag_0 = sval_0 & 0xC000;
            sval_0 = sval_0 & 0x3FFF;
            sval_1 = *(unsigned short*)(buf + 1 + 2);
            flag_1 = sval_1 & 0xC000;
            sval_1 = sval_1 & 0x3FFF;
            sval_2 = *(unsigned short*)(buf + 1 + 4);
            flag_2 = sval_2 & 0xC000;
            sval_2 = sval_2 & 0x3FFF;
            /* printf("    0x25 - NEQ DWORD - sval_0: 0x%04X ; ", sval_0);
            odv_scb_operation_flag_info(flag_0);
            printf(" ; sval_1: 0x%04X ; ", sval_1);
            odv_scb_operation_flag_info(flag_1);
            printf(" ; sval_2: 0x%04X ; ", sval_2);
            odv_scb_operation_flag_info(flag_2); */
            printf("    0x25 - mov %s%d, (%s%d != %s%d)", odv_scb_operation_flag_info(flag_0), sval_0, odv_scb_operation_flag_info(flag_1), sval_1, odv_scb_operation_flag_info(flag_2), sval_2);
            printf("\n");
            break;

        case 0x26:
            sval_0 = *(unsigned short*)(buf + 1);
            flag_0 = sval_0 & 0xC000;
            sval_0 = sval_0 & 0x3FFF;
            sval_1 = *(unsigned short*)(buf + 1 + 2);
            flag_1 = sval_1 & 0xC000;
            sval_1 = sval_1 & 0x3FFF;
            sval_2 = *(unsigned short*)(buf + 1 + 4);
            flag_2 = sval_2 & 0xC000;
            sval_2 = sval_2 & 0x3FFF;
            /*printf("    0x26 - EQ DWORD - sval_0: 0x%04X ; ", sval_0);
            odv_scb_operation_flag_info(flag_0);
            printf(" ; sval_1: 0x%04X ; ", sval_1);
            odv_scb_operation_flag_info(flag_1);
            printf(" ; sval_2: 0x%04X ; ", sval_2);
            odv_scb_operation_flag_info(flag_2);*/
            printf("    0x26 - mov %s%d, (%s%d == %s%d)", odv_scb_operation_flag_info(flag_0), sval_0, odv_scb_operation_flag_info(flag_1), sval_1, odv_scb_operation_flag_info(flag_2), sval_2);
            printf("\n");
            break;

        default:
            printf("    %02X - FUU - %08X %08X\n", opcode, *(unsigned int*)(buf + 1), *(unsigned int*)(buf + 1 + 4));
    }
}