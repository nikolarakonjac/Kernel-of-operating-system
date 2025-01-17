//
// Created by os on 8/28/22.
//

#ifndef PROJECT_BASE_V1_0_RISCV_HPP
#define PROJECT_BASE_V1_0_RISCV_HPP

#include "../lib/hw.h"
#include "../h/printing.hpp"
#include "../h/tcb.hpp"
//extern "C" void interruptRoutine();

class Riscv {
public:

    // maskira spoljasnje prekide
    static void lock();

    //demaskira spoljasnje prekide
    static void unlock();

    static void popSppSpie();

    static void interruptRoutine(); //prekidna rutina

    static void pushRegisters();

    static void popRegisters();

    // read register scause
    static uint64 r_scause();

    // write register scause
    static void w_scause(uint64 scause);

    // read register sepc
    static uint64 r_sepc();

    // write register sepc
    static void w_sepc(uint64 sepc);

    // read register stvec
    static uint64 r_stvec();

    // write register stvec
    static void w_stvec(uint64 stvec);

    // read register stval
    static uint64 r_stval();

    // write register stval
    static void w_stval(uint64 stval);

    enum BitMaskSip
    {
        SIP_SSIP = (1 << 1),
        SIP_STIP = (1 << 5),
        SIP_SEIP = (1 << 9),
    };

    // mask set register sip
    static void ms_sip(uint64 mask);

    // mask clear register sip
    static void mc_sip(uint64 mask);

    // procitaj sip registar
    static uint64 r_sip();

    // upisi u sip registar
    static void w_sip(uint64 sip);

    enum BitMaskSstatus
    {
        SSTATUS_SIE = (1 << 1),
        SSTATUS_SPIE = (1 << 5),
        SSTATUS_SPP = (1 << 8),
    };

    /*
     * spp -> govori iz kog rezima se dogodio prekid; 0 - korisnicki; 1 - sistemski
     * sie -> da li su maskirani spoljasnji prekidi; 0 - nisu; 1 - jesu
     * spie -> prethodna vrednost sie
     * */

    //postavlja na 1 bit iz sstatus registra u odnosu na masku{1(sie),5(spie),8(spp)}
    static void ms_sstatus(uint64 mask);


    //postavlja na 0 bit iz sstatus registra u odnosu na masku{1(sie),5(spie),8(spp)}
    static void mc_sstatus(uint64 mask);

    // procitaj sstatus registar
    static uint64 r_sstatus();

    // upisi u status registar
    static void w_sstatus(uint64 sstatus);

private:

    static void interruptRoutineHandler(); //u ovoj fji obradjujemo prekidnu rutinu
};

//implementacija nekih metoda
inline uint64 Riscv::r_scause()
{
    uint64 volatile scause;
    __asm__ volatile ("csrr %[scause], scause" : [scause] "=r"(scause));
    return scause;
}

inline void Riscv::w_scause(uint64 scause)
{
    __asm__ volatile ("csrw scause, %[scause]" : : [scause] "r"(scause));
}

inline uint64 Riscv::r_sepc()
{
    uint64 volatile sepc;
    __asm__ volatile ("csrr %[sepc], sepc" : [sepc] "=r"(sepc));
    return sepc;
}

inline void Riscv::w_sepc(uint64 sepc)
{
    __asm__ volatile ("csrw sepc, %[sepc]" : : [sepc] "r"(sepc));
}

inline uint64 Riscv::r_stvec()
{
    uint64 volatile stvec;
    __asm__ volatile ("csrr %[stvec], stvec" : [stvec] "=r"(stvec));
    return stvec;
}

inline void Riscv::w_stvec(uint64 stvec)
{
    __asm__ volatile ("csrw stvec, %[stvec]" : : [stvec] "r"(stvec));
}

inline uint64 Riscv::r_stval()
{
    uint64 volatile stval;
    __asm__ volatile ("csrr %[stval], stval" : [stval] "=r"(stval));
    return stval;
}

inline void Riscv::w_stval(uint64 stval)
{
    __asm__ volatile ("csrw stval, %[stval]" : : [stval] "r"(stval));
}

inline void Riscv::ms_sip(uint64 mask)
{
    __asm__ volatile ("csrs sip, %[mask]" : : [mask] "r"(mask));
}

inline void Riscv::mc_sip(uint64 mask)
{
    __asm__ volatile ("csrc sip, %[mask]" : : [mask] "r"(mask));
}

inline uint64 Riscv::r_sip()
{
    uint64 volatile sip;
    __asm__ volatile ("csrr %[sip], sip" : [sip] "=r"(sip));
    return sip;
}

inline void Riscv::w_sip(uint64 sip)
{
    __asm__ volatile ("csrw sip, %[sip]" : : [sip] "r"(sip));
}

inline void Riscv::ms_sstatus(uint64 mask)
{
    __asm__ volatile ("csrs sstatus, %[mask]" : : [mask] "r"(mask));
}

inline void Riscv::mc_sstatus(uint64 mask)
{
    __asm__ volatile ("csrc sstatus, %[mask]" : : [mask] "r"(mask));
}

inline uint64 Riscv::r_sstatus()
{
    uint64 volatile sstatus;
    __asm__ volatile ("csrr %[sstatus], sstatus" : [sstatus] "=r"(sstatus));
    return sstatus;
}

inline void Riscv::w_sstatus(uint64 sstatus)
{
    __asm__ volatile ("csrw sstatus, %[sstatus]" : : [sstatus] "r"(sstatus));
}

/*void Riscv::lock() {
    Riscv::mc_sstatus(Riscv::SSTATUS_SIE);
}

void Riscv::unlock() {
    Riscv::ms_sstatus(Riscv::SSTATUS_SIE);
}*/


#endif //PROJECT_BASE_V1_0_RISCV_HPP
