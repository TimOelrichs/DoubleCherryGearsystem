/*
 * Gearsystem - Sega Master System / Game Gear Emulator
 * Copyright (C) 2013  Ignacio Sanchez

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see http://www.gnu.org/licenses/ 
 * 
 */

#ifndef OPCODEED_NAMES_H
#define	OPCODEED_NAMES_H

static stOPCodeInfo kOPCodeEDNames[256] = {
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },

    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },

    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },

    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },

    { "IN B,(C)", 2, 0 },
    { "OUT (C),B", 2, 0 },
    { "SBC HL,BC", 2, 0 },
    { "LD ($%04X),BC", 4, 3 },
    { "NEG", 2, 0 },
    { "RETN", 2, 0 },
    { "IM 0", 2, 0 },
    { "LD I,A", 2, 0 },
    { "IN C,(C)", 2, 0 },
    { "OUT (C),C", 2, 0 },
    { "ADC HL,BC", 2, 0 },
    { "LD BC,($%04X)", 4, 3 },
    { "NEG [UNDOC]", 2, 0 },
    { "RETI", 2, 0 },
    { "IM 0 [UNDOC]", 2, 0 },
    { "LD R,A", 2, 0 },

    { "IN D,(C)", 2, 0 },
    { "OUT (C),D", 2, 0 },
    { "SBC HL,DE", 2, 0 },
    { "LD ($%04X),DE", 4, 3 },
    { "NEG [UNDOC]", 2, 0 },
    { "RETN [UNDOC]", 2, 0 },
    { "IM 1", 2, 0 },
    { "LD A,I", 2, 0 },
    { "IN E,(C)", 2, 0 },
    { "OUT (C),E", 2, 0 },
    { "ADC HL,DE", 2, 0 },
    { "LD DE,($%04X)", 4, 3 },
    { "NEG [UNDOC]", 2, 0 },
    { "RETN [UNDOC]", 2, 0 },
    { "IM 2", 2, 0 },
    { "LD A,R", 2, 0 },

    { "IN H,(C)", 2, 0 },
    { "OUT (C),H", 2, 0 },
    { "SBC HL,HL", 2, 0 },
    { "LD ($%04X),HL", 4, 3 },
    { "NEG [UNDOC]", 2, 0 },
    { "RETN [UNDOC]", 2, 0 },
    { "IM 0 [UNDOC]", 2, 0 },
    { "RRD", 2, 0 },
    { "IN L,(C)", 2, 0 },
    { "OUT (C),L", 2, 0 },
    { "ADC HL,HL", 2, 0 },
    { "LD HL,($%04X)", 4, 3 },
    { "NEG [UNDOC]", 2, 0 },
    { "RETN [UNDOC]", 2, 0 },
    { "IM 0 [UNDOC]", 2, 0 },
    { "RLD", 2, 0 },

    { "IN F,(C) [UNDOC]", 2, 0 },
    { "OUT (C),0 [UNDOC]", 2, 0 },
    { "SBC HL,SP", 2, 0 },
    { "LD ($%04X),SP", 4, 3 },
    { "NEG [UNDOC]", 2, 0 },
    { "RETN [UNDOC]", 2, 0 },
    { "IM 1 [UNDOC]", 2, 0 },
    { "INVALID", 2, 0 },
    { "IN A,(C)", 2, 0 },
    { "OUT (C),A", 2, 0 },
    { "ADC HL,SP", 2, 0 },
    { "LD SP,($%04X)", 4, 3 },
    { "NEG [UNDOC]", 2, 0 },
    { "RETN [UNDOC]", 2, 0 },
    { "IM 2 [UNDOC]", 2, 0 },
    { "INVALID", 2, 0 },

    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },

    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },

    { "LDI", 2, 0 },
    { "CPI", 2, 0 },
    { "INI", 2, 0 },
    { "OUTI", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "LDD", 2, 0 },
    { "CPD", 2, 0 },
    { "IND", 2, 0 },
    { "OUTD", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },

    { "LDIR", 2, 0 },
    { "CPIR", 2, 0 },
    { "INIR", 2, 0 },
    { "OTIR", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "LDDR", 2, 0 },
    { "CPDR", 2, 0 },
    { "INDR", 2, 0 },
    { "OTDR", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },

    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },

    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },

    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },

    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 },
    { "INVALID", 2, 0 }
};

#endif	/* OPCODEED_NAMES_H */

