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
        unsigned int n;			// Номер варианта
        unsigned int cmpr1;		// Уставка сравнения для модуля ШИМ (стойка A)
        unsigned int cmpr2;		// Уставка сравнения для модуля ШИМ (стойка B)
        unsigned int cmpr3;		// Уставка сравнения для модуля ШИМ (стойка C)
        unsigned int tpr;		// Период счётчика модуля ШИМ (для счёта вверх-вниз)
        unsigned int dt;		// Мёртвое время
        unsigned int adcSpeed;	// Код АЦП: скорость с тахогенератора
        unsigned int qepCounter;// Счётчик импульсов инкрементального энкодера
		unsigned int hallSensor;// Показания датчика Холла
		unsigned int iA;		// Код АЦП: ток фазы А (или ток якоря для ДПТ)
		unsigned int iB;		// Код АЦП: ток фазы B (или ток ОВ для ДПТ)
		unsigned int iC;		// Код АЦП: ток фазы С (для ДПТ не используется)
		int fault;				// Код аварии
		float load;				// Нагрузка двигателя (Нм)
		float time;				// Время (с)
        void (*Init)(volatile struct MODELDATA*);
        void (*Execute)(volatile struct MODELDATA*);
        } MODELDATA ;

typedef volatile struct MODELDATA Tmodel;

#define MODEL_DEFAULTS { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, Model_Init, Model_Execute}

void Model_Init(Tmodel*);
void Model_Execute(Tmodel*);


