// model.h
#include "IQmathLib.h"

// faults
#define ILLEGAL_STUDENT_NUMBER 1
#define MAX_CURRENT_FAULT 2
#define MAX_SPEED_FAULT 3

// motor types (for internal use)
#define INDUCTION_MOTOR 1
#define SYNC_MOTOR 2
#define DC_MOTOR 3
#define SRD 4
#define SyncRM 5

#define PI 3.1415926535897932384626433832795
#define INV_2PI 0.15915494309189533576888376337251

typedef struct  MODELDATA {
        unsigned int n;			// ����� ��������
        unsigned int cmpr1;		// ������� ��������� ��� ������ ��� (������ A)
        unsigned int cmpr2;		// ������� ��������� ��� ������ ��� (������ B)
        unsigned int cmpr3;		// ������� ��������� ��� ������ ��� (������ C)
        unsigned int tpr;		// ������ �������� ������ ��� (��� ����� �����-����)
        unsigned int dt;		// ̸����� �����
        unsigned int adcSpeed;	// ��� ���: �������� � ��������������
        unsigned int qepCounter;// ������� ��������� ���������������� ��������
		unsigned int hallSensor;// ��������� ������� �����
		unsigned int iA;		// ��� ���: ��� ���� � (��� ��� ����� ��� ���)
		unsigned int iB;		// ��� ���: ��� ���� B (��� ��� �� ��� ���)
		unsigned int iC;		// ��� ���: ��� ���� � (��� ��� �� ������������)
		int fault;				// ��� ������
		float load;				// �������� ��������� (��)
		float time;				// ����� (�)
        void (*Init)(volatile struct MODELDATA*);
        void (*Execute)(volatile struct MODELDATA*);
        } MODELDATA ;

typedef volatile struct MODELDATA Tmodel;

#define MODEL_DEFAULTS { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, Model_Init, Model_Execute}

void Model_Init(Tmodel*);
void Model_Execute(Tmodel*);


