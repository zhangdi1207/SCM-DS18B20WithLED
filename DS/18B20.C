#include"head.h"

/**************************************
��λDS18B20,������豸�Ƿ����
**************************************/
void DS18B20_Reset()
{
    CY = 1;
    while (CY)
    {
        DQ = 0;                     //�ͳ��͵�ƽ��λ�ź�
        DelayXus(540);              //��ʱ����480us
        DQ = 1;                     //�ͷ�������
        DelayXus(60);               //�ȴ�60us
        CY = DQ;                    //����������
        DelayXus(240);              //�ȴ��豸�ͷ�������
        DelayXus(180);
    }
}

/**************************************
��DS18B20��1�ֽ�����
**************************************/
uchar DS18B20_ReadByte()
{
    uchar i;
    uint dat = 0;

    for (i=0; i<8; i++)             //8λ������
    {
        dat >>= 1;
        DQ = 0;                     //��ʼʱ��Ƭ
        nop();                //��ʱ�ȴ�
        DQ = 1;                     //׼������
        nop();                //������ʱ
        if (DQ) 
			dat |= 0x80;        //��ȡ����
        DelayXus(60);               //�ȴ�ʱ��Ƭ����
    }

    return dat;
}

/**************************************
��DS18B20д1�ֽ�����
**************************************/
void DS18B20_WriteByte(uchar dat)
{
    char i,j;

    for (i=0; i<8; i++)             //8λ������
    {
		j=dat&0x01;
		dat>>=1;
        DQ = 0;                     //��ʼʱ��Ƭ
        nop();                //��ʱ�ȴ�
        DQ = j;
        DelayXus(60);               //�ȴ�ʱ��Ƭ����
        DQ = 1;                     //�ָ�������
        nop();                //�ָ���ʱ
    }
}

int readOneTemp()
{	
	uchar a,b;
	int t;
	DS18B20_Reset(  );
	DS18B20_WriteByte(0xCC);
	DS18B20_WriteByte(0x44);   //��ʼת������
    while (!DQ);                    //�ȴ�ת�����
    DS18B20_Reset();                //�豸��λ
    DS18B20_WriteByte(0xCC);        //����ROM����
    DS18B20_WriteByte(0xBE);

	a=DS18B20_ReadByte();
	b=DS18B20_ReadByte();
	t=b;
	t<<=4;
	a>>=4;
	t|=a;
	return t;
}
