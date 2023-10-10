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

#ifndef OPCODEFD_NAMES_H
#define	OPCODEFD_NAMES_H

static stOPCodeInfo kOPCodeFDNames[256] = {
    { "NOP", 2, 0 },
    { "LD BC,$%04X", 4, 3 },
    { "LD (BC),A", 2, 0 },
    { "INC BC", 2, 0 },
    { "INC B", 2, 0 },
    { "DEC B", 2, 0 },
    { "LD B,$%02X", 3, 2 },
    { "RLCA", 2, 0 },
    { "EX AF,AF'", 2, 0 },
    { "ADD IY,BC", 2, 0 },
    { "LD A,(BC)", 2, 0 },
    { "DEC BC", 2, 0 },
    { "INC C", 2, 0 },
    { "DEC C", 2, 0 },
    { "LD C,$%02X", 3, 2 },
    { "RRCA", 2, 0 },

    { "DJNZ $%04X  [%+d]", 3, 5 },
    { "LD DE,$%04X", 4, 3 },
    { "LD (DE),A", 2, 0 },
    { "INC DE", 2, 0 },
    { "INC D", 2, 0 },
    { "DEC D", 2, 0 },
    { "LD D,$%02X", 3, 2 },
    { "RLA", 2, 0 },
    { "JR $%04X  [%+d]", 3, 5 },
    { "ADD IY,DE", 2, 0 },
    { "LD A,(DE)", 2, 0 },
    { "DEC DE", 2, 0 },
    { "INC E", 2, 0 },
    { "DEC E", 2, 0 },
    { "LD E,$%02X", 3, 2 },
    { "RRA", 2, 0 },

    { "JR NZ,$%04X  [%+d]", 3, 5 },
    { "LD IY,$%04X", 4, 3 },
    { "LD ($%04X),IY", 4, 3 },
    { "INC IY", 2, 0 },
    { "INC IYh [UNDOC]", 2, 0 },
    { "DEC IYh [UNDOC]", 2, 0 },
    { "LD IYh,$%02X [UNDOC]", 3, 2 },
    { "DAA", 2, 0 },
    { "JR Z,$%04X  [%+d]", 3, 5 },
    { "ADD IY,IY", 2, 0 },
    { "LD IY,($%04X)", 4, 3 },
    { "DEC IY", 2, 0 },
    { "INC IYl [UNDOC]", 2, 0 },
    { "DEC IYl [UNDOC]", 2, 0 },
    { "LD IYl,$%02X [UNDOC]", 3, 2 },
    { "CPL", 2, 0 },

    { "JR NC,$%04X  [%+d]", 3, 5 },
    { "LD SP,$%04X", 4, 3 },
    { "LD ($%04X),A", 4, 3 },
    { "INC SP", 2, 0 },
    { "INC (IY%+d)", 3, 4 },
    { "DEC (IY%+d)", 3, 4 },
    { "LD (IY%+d),$%02X", 4, 6 },
    { "SCF", 2, 0 },
    { "JR C,$%04X  [%+d]", 3, 5 },
    { "ADD IY,SP", 2, 0 },
    { "LD A,($%04X)", 4, 3 },
    { "DEC SP", 2, 0 },
    { "INC A", 2, 0 },
    { "DEC A", 2, 0 },
    { "LDA,$%02X", 3, 2 },
    { "CCF", 2, 0 },

    { "LD B,B", 2, 0 },
    { "LD B,C", 2, 0 },
    { "LD B,D", 2, 0 },
    { "LD B,E", 2, 0 },
    { "LD B,IYh [UNDOC]", 2, 0 },
    { "LD B,IYl [UNDOC]", 2, 0 },
    { "LD B,(IY%+d)", 3, 4 },
    { "LD B,A", 2, 0 },
    { "LD C,B", 2, 0 },
    { "LD C,C", 2, 0 },
    { "LD C,D", 2, 0 },
    { "LD C,E", 2, 0 },
    { "LD C,IYh [UNDOC]", 2, 0 },
    { "LD C,IYl [UNDOC]", 2, 0 },
    { "LD C,(IY%+d)", 3, 4 },
    { "LD C,A", 2, 0 },

    { "LD D,B", 2, 0 },
    { "LD D,C", 2, 0 },
    { "LD D,D", 2, 0 },
    { "LD D,E", 2, 0 },
    { "LD D,IYh [UNDOC]", 2, 0 },
    { "LD D,IYl [UNDOC]", 2, 0 },
    { "LD D,(IY%+d)", 3, 4 },
    { "LD D,A", 2, 0 },
    { "LD E,B", 2, 0 },
    { "LD E,C", 2, 0 },
    { "LD E,D", 2, 0 },
    { "LD E,E", 2, 0 },
    { "LD E,IYh [UNDOC]", 2, 0 },
    { "LD E,IYl [UNDOC]", 2, 0 },
    { "LD E,(IY%+d)", 3, 4 },
    { "LD E,A", 2, 0 },

    { "LD IYh,B [UNDOC]", 2, 0 },
    { "LD IYh,C [UNDOC]", 2, 0 },
    { "LD IYh,D [UNDOC]", 2, 0 },
    { "LD IYh,E [UNDOC]", 2, 0 },
    { "LD IYh,IYh [UNDOC]", 2, 0 },
    { "LD IYh,IYl [UNDOC]", 2, 0 },
    { "LD H,(IY%+d)", 3, 4 },
    { "LD IYh,A [UNDOC]", 2, 0 },
    { "LD IYl,B [UNDOC]", 2, 0 },
    { "LD IYl,C [UNDOC]", 2, 0 },
    { "LD IYl,D [UNDOC]", 2, 0 },
    { "LD IYl,E [UNDOC]", 2, 0 },
    { "LD IYl,IYh [UNDOC]", 2, 0 },
    { "LD IYl,IYl [UNDOC]", 2, 0 },
    { "LD L,(IY%+d)", 3, 4 },
    { "LD IYl,A [UNDOC]", 2, 0 },

    { "LD (IY%+d),B", 3, 4 },
    { "LD (IY%+d),C", 3, 4 },
    { "LD (IY%+d),D", 3, 4 },
    { "LD (IY%+d),E", 3, 4 },
    { "LD (IY%+d),H", 3, 4 },
    { "LD (IY%+d),L", 3, 4 },
    { "HALT", 2, 0 },
    { "LD (IY%+d),A", 3, 4 },
    { "LD A,B", 2, 0 },
    { "LD A,C", 2, 0 },
    { "LD A,D", 2, 0 },
    { "LD A,E", 2, 0 },
    { "LD A,IYh [UNDOC]", 2, 0 },
    { "LD A,IYl [UNDOC]", 2, 0 },
    { "LD A,(IY%+d)", 3, 4 },
    { "LD A,A", 2, 0 },

    { "ADD A,B", 2, 0 },
    { "ADD A,C", 2, 0 },
    { "ADD A,D", 2, 0 },
    { "ADD A,E", 2, 0 },
    { "ADD A,IYh [UNDOC]", 2, 0 },
    { "ADD A,IYl [UNDOC]", 2, 0 },
    { "ADD A,(IY%+d)", 3, 4 },
    { "ADD A,A", 2, 0 },
    { "ADC A,B", 2, 0 },
    { "ADC A,C", 2, 0 },
    { "ADC A,D", 2, 0 },
    { "ADC A,E", 2, 0 },
    { "ADC A,IYh [UNDOC]", 2, 0 },
    { "ADC A,IYl [UNDOC]", 2, 0 },
    { "ADC A,(IY%+d)", 3, 4 },
    { "ADC A,A", 2, 0 },

    { "SUB B", 2, 0 },
    { "SUB C", 2, 0 },
    { "SUB D", 2, 0 },
    { "SUB E", 2, 0 },
    { "SUB IYh [UNDOC]", 2, 0 },
    { "SUB IYl [UNDOC]", 2, 0 },
    { "SUB (IY%+d)", 3, 4 },
    { "SUB A", 2, 0 },
    { "SBC A,B", 2, 0 },
    { "SBC A,C", 2, 0 },
    { "SBC A,D", 2, 0 },
    { "SBC A,E", 2, 0 },
    { "SBC A,IYh [UNDOC]", 2, 0 },
    { "SBC A,IYl [UNDOC]", 2, 0 },
    { "SBC A,(IY%+d)", 3, 4 },
    { "SBC A,A", 2, 0 },

    { "AND B", 2, 0 },
    { "AND C", 2, 0 },
    { "AND D", 2, 0 },
    { "AND E", 2, 0 },
    { "AND IYh [UNDOC]", 2, 0 },
    { "AND IYl [UNDOC]", 2, 0 },
    { "AND (IY%+d)", 3, 4 },
    { "AND A", 2, 0 },
    { "XOR B", 2, 0 },
    { "XOR C", 2, 0 },
    { "XOR D", 2, 0 },
    { "XOR E", 2, 0 },
    { "XOR IYh [UNDOC]", 2, 0 },
    { "XOR IYl [UNDOC]", 2, 0 },
    { "XOR (IY%+d)", 3, 4 },
    { "XOR A", 2, 0 },

    { "OR B", 2, 0 },
    { "OR C", 2, 0 },
    { "OR D", 2, 0 },
    { "OR E", 2, 0 },
    { "OR IYh [UNDOC]", 2, 0 },
    { "OR IYl [UNDOC]", 2, 0 },
    { "OR (IY%+d)", 3, 4 },
    { "OR A", 2, 0 },
    { "CP B", 2, 0 },
    { "CP C", 2, 0 },
    { "CP D", 2, 0 },
    { "CP E", 2, 0 },
    { "CP IYh [UNDOC]", 2, 0 },
    { "CP IYl [UNDOC]", 2, 0 },
    { "CP (IY%+d)", 3, 4 },
    { "CP A", 2, 0 },

    { "RET NZ", 2, 0 },
    { "POP BC", 2, 0 },
    { "JP NZ,$%04X", 4, 3 },
    { "JP $%04X", 4, 3 },
    { "CALL NZ,$%04X", 4, 3 },
    { "PUSH BC", 2, 0 },
    { "ADD A,$%02X", 3, 2 },
    { "RST ", 2, 0 },
    { "RET Z", 2, 0 },
    { "RET", 2, 0 },
    { "JP Z,$%04X", 4, 3 },
    { "CB PREFIX", 2, 0 },
    { "CALL Z,$%04X", 4, 3 },
    { "CALL $%04X", 4, 3 },
    { "ADC A,$%02X", 3, 2 },
    { "RST 08H", 2, 0 },

    { "RET NC", 2, 0 },
    { "POP DE", 2, 0 },
    { "JP NC,$%04X", 4, 3 },
    { "OUT ($%02X),A", 3, 2 },
    { "CALL NC,$%04X", 4, 3 },
    { "PUSH DE", 2, 0 },
    { "SUB $%02X", 3, 2 },
    { "RST 10H", 2, 0 },
    { "RET C", 2, 0 },
    { "EXX", 2, 0 },
    { "JP C,$%04X", 4, 3 },
    { "IN A,($%02X)", 3, 2 },
    { "CALL C,$%04X", 4, 3 },
    { "DD PREFIX", 2, 0 },
    { "SBC A,$%02X", 3, 2 },
    { "RST 18H", 2, 0 },

    { "RET PO", 2, 0 },
    { "POP IY", 2, 0 },
    { "JP PO,$%04X", 4, 3 },
    { "EX (SP),IY", 2, 0 },
    { "CALL PO,$%04X", 4, 3 },
    { "PUSH IY", 2, 0 },
    { "AND $%02X", 3, 2 },
    { "RST 20H", 2, 0 },
    { "RET PE", 2, 0 },
    { "JP (IY)", 2, 0 },
    { "JP PE,$%04X", 4, 3 },
    { "EX DE,HL", 2, 0 },
    { "CALL PE,$%04X", 4, 3 },
    { "ED PREFIX", 2, 0 },
    { "XOR $%02X", 3, 2 },
    { "RST 28H", 2, 0 },

    { "RET P", 2, 0 },
    { "POP AF", 2, 0 },
    { "JP P,$%04X", 4, 3 },
    { "DI", 2, 0 },
    { "CALL P,$%04X", 4, 3 },
    { "PUSH AF", 2, 0 },
    { "OR $%02X", 3, 2 },
    { "RST 30H", 2, 0 },
    { "RET M", 2, 0 },
    { "LD SP,IY", 2, 0 },
    { "JP M,$%04X", 4, 3 },
    { "EI", 2, 0 },
    { "CALL M,$%04X", 4, 3 },
    { "FD PREFIX", 2, 0 },
    { "CP $%02X", 3, 2 },
    { "RST 38H", 2, 0 }
};

#endif	/* OPCODEFD_NAMES_H */

