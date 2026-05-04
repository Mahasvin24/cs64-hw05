#include <iostream>     // for use of cin, cout, endl
#include <string>       // for use of strings, string member functions
#include <cmath>        // for use of pow(x,y) function
// NO OTHER LIBRARIES ARE ALLOWED!

using namespace std;

// function: disassemble takes in a string representing
//          an assembled MIPS instruction as a string
//          and returns the instruction itself
//
//          This is a limited disassembler: we can safely assume the input is:
//          a) legitimate (an actual MIPS instruction)
//          b) is ONLY an I-type and ONLY one of: addi, addiu, andi, ori, slti, sltiu
//          c) has ONLY registers $t0 thru $t7, or $s0 thru $s7 in the instruction
//
string disassemble( string hex ) {

    // You want to retrieve all the separate fields of an I-type instruction
    //      to help you figure out what the assembly instruction is.
    //
    // HINT: Use bitwise masking and bit-shifting to isolate the 
    //      different parts of the hex instruction!
    
    string sol;
    int opcode, rs, rt, u_immediate;
    short s_immediate;

    // find number (not as a string)
    unsigned num = 0;
    for (char c : hex) {
        int val = c - '0';
        if ('A' <= c && c <= 'F') val = c - 'A' + 10;

        num *= 16;
        num += val;
    }

    // split into components
    opcode      = (num & 0b11111100000000000000000000000000) >> 26;
    rs          = (num & 0b00000011111000000000000000000000) >> 21;
    rt          = (num & 0b00000000000111110000000000000000) >> 16;
    s_immediate = (num & 0x0000FFFF);
    u_immediate = (num & 0x0000FFFF);

    // add instruction name
    switch (opcode) {
        case 8: sol += "addi"; break;
        case 9: sol += "addiu"; break;
        case 10: sol += "slti"; break;
        case 11: sol += "sltiu"; break;
        case 12: sol += "andi"; break;
        case 13: sol += "ori"; break;
    }
    
    sol += " ";

    // add rt
    if (8 <= rt && rt <= 15) {
        sol += "$t";
        sol += to_string(rt - 8);
    } else {
        sol += "$s";
        sol += to_string(rt - 16);
    }

    sol += ", ";

    // add rs
    if (8 <= rs && rs <= 15) {
        sol += "$t";
        sol += to_string(rs - 8);
    } else {
        sol += "$s";
        sol += to_string(rs - 16);
    }

    sol += ", ";

    // adjust opcode being unsigned or signed
    if (opcode == 9 || opcode == 11) {
        sol += to_string(u_immediate);
    } else {
        sol += to_string(s_immediate);
    }
 
    return sol;
}

int main() {
// Do NOT change ANY code in main() function!!
//      or you will fail this task (get a zero)

    string hex, inst;
    
    cout << "Enter your assembled instruction as a hex number: 0x";
    cin >> hex;
    
    inst = disassemble( hex );
    cout << "Your instruction is:\n" << inst << endl;

    return 0;
}
