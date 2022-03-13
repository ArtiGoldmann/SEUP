/* Основной файл работы с моделью двигателя.
 * В функции "main()" инициализируется периферия МК F28035 - настраивается тактирование,
 * инициализируется flash-память. Модуль ePWM1 настраивается на работу с частотой 5 кГц
 * при счёте "вверх-вниз", настраивается прерывание по достижении счётчиком нуля.
 *
 * Затем происходит инициализация модели двигателя, после чего разрешаются прерывания
 * и начинает выполняться бесконечный цикл.
 *
 * В функции-обработчике прерывания вызывается пустая функция "controlSystem()", в которой
 * пользователь может реализовать свою систему управления. Затем вызывается функция
 * расчёта модели двигателя.
 */

// Подключение необходимых заголовочных файлов
#include "DSP28x_Project.h"
#include "model.h"

// Определение структуры модели двигателя
MODELDATA drive = MODEL_DEFAULTS;

void controlSystem (){

	drive.cmpr1 = 0;
	drive.cmpr2 = 0;
	drive.cmpr3 = 0;

}

// Прототип функции-обработчика прерывания
interrupt void controlIsr(void);

// Основная функция "main()", в которой происходит инициализация системы
int main(void) {
	// Настройка периферии микроконтроллера
	InitSysCtrl();
	memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, &RamfuncsLoadEnd - &RamfuncsLoadStart);
	InitFlash();
    InitPieCtrl();
    InitPieVectTable();

    // Настройка таймера для прерываний на частоте 5 кГц
    EALLOW;
    EPwm1Regs.TBPRD = 6000;
    EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
    EPwm1Regs.ETSEL.bit.INTEN = 1;
    EPwm1Regs.ETSEL.bit.INTSEL = TB_CTR_ZERO;
    EPwm1Regs.ETPS.bit.INTPRD = 1;

    PieVectTable.EPWM1_INT = controlIsr;
    PieCtrlRegs.PIEIER3.all = M_INT1;
    IER |= M_INT3;
    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;

    CpuTimer0Regs.PRD.all = 0xFFFFFFFF;
    CpuTimer0Regs.TCR.bit.TSS = 0;
    EDIS;

	// В первую очередь необходимо задать вариант в переменной "n"
	// и внутренний период таймера ШИМ 6000
    // TPR = Fcpu / Fpwm / 2 = 60000000 / 5000 / 2 = 6000
    // Доп. деление на 2 нужно, т.к. таймер считает вверх-вниз
	drive.n = 29;
	drive.tpr = 6000;

	// Теперь нужно вызвать функцию "Init" для инициализации модели
	drive.Init(&drive);

	// Глобально разрешаем прерывания
	EINT;

	// Бесконечный цикл
	while (1) {

	}
}

// Прерывание для расчёта модели двигателя
interrupt void controlIsr(void) {
	// Пользовательская функция с расчётом системы управления,
	// в которой осуществляется расчёт и присвоение уставок сравнения cmpr1, cmpr2, cmpr3
	controlSystem();

	// Выполнение модели двигателя
	drive.Execute(&drive);

	// Очистка флагов прерывания
	EPwm1Regs.ETCLR.bit.INT = 1;
	PieCtrlRegs.PIEACK.bit.ACK3 = 1;
}
