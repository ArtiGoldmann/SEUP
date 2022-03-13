/* �������� ���� ������ � ������� ���������.
 * � ������� "main()" ���������������� ��������� �� F28035 - ������������� ������������,
 * ���������������� flash-������. ������ ePWM1 ������������� �� ������ � �������� 5 ���
 * ��� ����� "�����-����", ������������� ���������� �� ���������� ��������� ����.
 *
 * ����� ���������� ������������� ������ ���������, ����� ���� ����������� ����������
 * � �������� ����������� ����������� ����.
 *
 * � �������-����������� ���������� ���������� ������ ������� "controlSystem()", � �������
 * ������������ ����� ����������� ���� ������� ����������. ����� ���������� �������
 * ������� ������ ���������.
 */

// ����������� ����������� ������������ ������
#include "DSP28x_Project.h"
#include "model.h"

// ����������� ��������� ������ ���������
MODELDATA drive = MODEL_DEFAULTS;

void controlSystem (){

	drive.cmpr1 = 0;
	drive.cmpr2 = 0;
	drive.cmpr3 = 0;

}

// �������� �������-����������� ����������
interrupt void controlIsr(void);

// �������� ������� "main()", � ������� ���������� ������������� �������
int main(void) {
	// ��������� ��������� ����������������
	InitSysCtrl();
	memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, &RamfuncsLoadEnd - &RamfuncsLoadStart);
	InitFlash();
    InitPieCtrl();
    InitPieVectTable();

    // ��������� ������� ��� ���������� �� ������� 5 ���
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

	// � ������ ������� ���������� ������ ������� � ���������� "n"
	// � ���������� ������ ������� ��� 6000
    // TPR = Fcpu / Fpwm / 2 = 60000000 / 5000 / 2 = 6000
    // ���. ������� �� 2 �����, �.�. ������ ������� �����-����
	drive.n = 29;
	drive.tpr = 6000;

	// ������ ����� ������� ������� "Init" ��� ������������� ������
	drive.Init(&drive);

	// ��������� ��������� ����������
	EINT;

	// ����������� ����
	while (1) {

	}
}

// ���������� ��� ������� ������ ���������
interrupt void controlIsr(void) {
	// ���������������� ������� � �������� ������� ����������,
	// � ������� �������������� ������ � ���������� ������� ��������� cmpr1, cmpr2, cmpr3
	controlSystem();

	// ���������� ������ ���������
	drive.Execute(&drive);

	// ������� ������ ����������
	EPwm1Regs.ETCLR.bit.INT = 1;
	PieCtrlRegs.PIEACK.bit.ACK3 = 1;
}
