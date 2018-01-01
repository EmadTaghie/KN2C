#include "transmitter.h"
#include <QSerialPortInfo>

Transmitter::Transmitter(QString port, OutputBuffer* buffer, WorldModel *wm, QObject *parent) :
    QObject(parent),
    _serialport(this),
    _timer(this),
    _buffer(buffer),
    _wm(wm)
{
    qDebug() << "Transmitter Initialization...";
    //if (WIRELESSBOARDVERSION == 1)
    if (true)
    {
        _serialport.setPortName("/dev/ttyACM0");
        while(!_serialport.open(QSerialPort::ReadWrite)); // test
        //_serialport.open(QSerialPort::WriteOnly);
        qint32 baud = 2000000;
        _serialport.setBaudRate(baud,QSerialPort::Output);
    }
    else
    {
        _serialport.setPort(QSerialPortInfo::availablePorts()[0]);
        //_serialport.setPortName("/dev/ttyACM0");
        //while(!_serialport.open(QSerialPort::ReadWrite)); // test
        _serialport.open(QSerialPort::WriteOnly);
        //qint32 baud = 2000000;
        //_serialport.setBaudRate(baud,QSerialPort::Output);
        _serialport.setBaudRate(QSerialPort::Baud115200);
    }
    _serialport.setDataBits(QSerialPort::DataBits::Data8);
    _serialport.setStopBits(QSerialPort::OneStop);
    _serialport.setFlowControl(QSerialPort::NoFlowControl);
    _serialport.setParity(QSerialPort::NoParity);
    qDebug() << _serialport.errorString();
    //connect(&_serialport, SIGNAL(readyRead()), this, SLOT(serialRead()));


    _timer.setInterval(TRANSMITTER_TIMER);
    //@mparchin: change in send methode
    if (WIRELESSBOARDVERSION == 1)
        connect(&_timer,SIGNAL(timeout()), this, SLOT(sendPacketNewWB()));
    else
        connect(&_timer,SIGNAL(timeout()), this, SLOT(sendPacket()));

    qDebug() << "Port: " << port;

    memset(readbuffer, 0, 120);
    read_state = PRE_0;
}
//{
//    qDebug() << "Transmitter Initialization...";

//    _serialport.setPortName(port);
//    _serialport.open(QIODevice::ReadWrite);
//    _serialport.setBaudRate(QSerialPort::Baud115200);
//    _serialport.setDataBits(QSerialPort::Data8);
//    _serialport.setStopBits(QSerialPort::OneStop);
//    _serialport.setFlowControl(QSerialPort::NoFlowControl);
//    _serialport.setParity(QSerialPort::NoParity);
//    qDebug() << _serialport.errorString();
//    //connect(&_serialport, SIGNAL(readyRead()), this, SLOT(serialRead()));

//    _timer.setInterval(TRANSMITTER_TIMER);
//    connect(&_timer,SIGNAL(timeout()), this, SLOT(sendPacket()));
//    qDebug() << "Port: " << port;

//    memset(readbuffer, 0, 120);
//    read_state = PRE_0;
//}

void Transmitter::Start()
{
    _state=true;
    _timer.start();
}

void Transmitter::Stop()
{
    _state=false;
    _timer.stop();
}

//@mparchin: send methode
void Transmitter::sendPacketNewWB()
{
    QByteArray pck = _buffer-> wpck.getPacketNewWB();
    if (_state)
    {
        fps.Pulse();
        for (int i = 0;i < pck.count() / 25; i++)
        {
            /*QByteArray head,body;
            head.clear();
            body.clear();
            for (int j = 0; j < 4 ;j++)
                head.append(pck.data()[i*25 + j]);
            for (int j = 4; j < 25 ;j++)
                body.append(pck.data()[i*25 + j]);
            _serialport.write(head);
            _serialport.waitForBytesWritten(1000);
            _serialport.waitForReadyRead(1000);
            char data;
            _serialport.getChar(&data);
            //qDebug() << data << endl;
            _serialport.write(body);
            _serialport.waitForBytesWritten(1000);
            _serialport.waitForReadyRead(1000);
            _serialport.getChar(&data);
            qDebug() << data << endl;*/
            QByteArray data;
            data.clear();
            for (int j = 0; j < 25 ;j++)
                data.append(pck.data()[i*25 + j]);
            _serialport.write(data);
            //_serialport.waitForBytesWritten(1000);
            _serialport.waitForReadyRead(1000);
            char readData;
            _serialport.getChar(&readData);
            QString str = QString::number(QChar(readData).unicode());
            str = QString::number(str.toInt(),16).toUpper();
            qDebug() << str << endl;
        }
    }
}

void Transmitter::sendPacket()
{
    QElapsedTimer testTimer;
    testTimer.start();
    if(_state)
    {
        QByteArray pck = _buffer->wpck.GetPacket();
        QString log;
        log+= "SerialData[" + QString::number(pck.size()) + "]: ";
        log+= pck.mid(0,2).toHex();
        log+= " ";
        log+= pck.mid(2,1).toHex();
        log+= " ";
        log+= pck.mid(3,1).toHex();
        log+= " ";
        log+= pck.mid(4,1).toHex();
        log+= " ";
        log+= pck.mid(5,2).toHex();
        log+= " ";
        log+= pck.mid(7,2).toHex();
        log+= " ";
        log+= pck.mid(9,2).toHex();
        log+= " ";
        log+= pck.mid(11,2).toHex();
        log+= " ";
        log+= pck.mid(13,1).toHex();
        log+= " ";
        log+= pck.mid(14,1).toHex();
        log+= " ";
        log+= pck.mid(15,1).toHex();
        if(pck.size() > 16) log+= " ...";
        log+= "\n";

        //cout << log.toStdString();
        //cout.flush();

        fps.Pulse();
        _serialport.write(pck);

        //        QByteArray debug;
        //        debug.append(QByteArray::fromHex("000102030405060708090a0b0c0d0e0f"));
        //        log+= "SeialData[" + QString::number(debug.size()) + "]: ";
        //        log+= debug.toHex();
        //        qDebug() << log;
        //        _serialport.port->write(debug);
    }
    qint64 difference=testTimer.nsecsElapsed();
    //qDebug()<<"send time:"<<QString::number(difference);
}

void Transmitter::serialRead()
{
    QElapsedTimer testTimer;
    testTimer.start();
    while (_serialport.bytesAvailable())
    {
        char data;
        _serialport.getChar(&data);
        //qDebug() << "sr" << QByteArray(&data, 1).toHex();
        if(read_state == PRE_0 && data == (signed char)0xa5)
        {
            read_state = PRE_1;
        }
        else if (read_state == PRE_1 && data == 0x5a)
        {
            read_state = PRE_2;
        }
        else if (read_state == PRE_1 && data != 0x5a)
        {
            read_state = PRE_0;
        }
        else if (read_state >= PRE_2)
        {
            readbuffer[read_state++] = data;
            if(read_state == 120)
            {
                read_state = PRE_0;
                //QByteArray d(readbuffer, 120);
                //qDebug() << "serialRead" << d.toHex();
                for(int i=0; i<12; i++)
                {
                    _wm->ourRobot[i].rd.M0 = readbuffer[1 + i*10]*256 + readbuffer[0 + i*10];
                    _wm->ourRobot[i].rd.M1 = readbuffer[3 + i*10]*256 + readbuffer[2 + i*10];
                    _wm->ourRobot[i].rd.M2 = readbuffer[5 + i*10]*256 + readbuffer[4 + i*10];
                    _wm->ourRobot[i].rd.M3 = readbuffer[7 + i*10]*256 + readbuffer[6 + i*10];
                    _wm->ourRobot[i].rd.KCK = readbuffer[8 + i*10];
                    _wm->ourRobot[i].rd.CHP = readbuffer[9 + i*10];
                }
                updateVel2();
            }
        }
    }
    qint64 difference=testTimer.nsecsElapsed();
    qDebug()<<"recieve time:"<<QString::number(difference);
}

void Transmitter::updateVel2()
{
    for(int i=0; i<12; i++)
    {
        double rotate[3][4],speed[3];

        rotate[0][0] = 0.3489;
        rotate[0][1] = 0.2965;
        rotate[0][2] = -0.2965;
        rotate[0][3] = -0.3489;
        rotate[1][0] = -0.3963;
        rotate[1][1] = 0.3963;
        rotate[1][2] = 0.3963;
        rotate[1][3] = -0.3963;
        rotate[2][0] = -3.1137;
        rotate[2][1] = -2.4418;
        rotate[2][2] = -2.4418;
        rotate[2][3] = -3.1137;

        speed[0] = rotate[0][0] * _wm->ourRobot[i].rd.M0 + rotate[0][1] * _wm->ourRobot[i].rd.M1 + rotate[0][2] * _wm->ourRobot[i].rd.M2 + rotate[0][3] * _wm->ourRobot[i].rd.M3;
        speed[1] = rotate[1][0] * _wm->ourRobot[i].rd.M0 + rotate[1][1] * _wm->ourRobot[i].rd.M1 + rotate[1][2] * _wm->ourRobot[i].rd.M2 + rotate[1][3] * _wm->ourRobot[i].rd.M3;
        speed[2] = rotate[2][0] * _wm->ourRobot[i].rd.M0 + rotate[2][1] * _wm->ourRobot[i].rd.M1 + rotate[2][2] * _wm->ourRobot[i].rd.M2 + rotate[2][3] * _wm->ourRobot[i].rd.M3;

        speed[0] /= 1375.14;
        speed[1] /= 1375.14;
        speed[2] /= 1375.14;

        _wm->ourRobot[i].vel2.loc.x = cos(_wm->ourRobot[i].pos.dir) * speed[0] - sin(_wm->ourRobot[i].pos.dir) * speed[1];
        _wm->ourRobot[i].vel2.loc.y = sin(_wm->ourRobot[i].pos.dir) * speed[0] + cos(_wm->ourRobot[i].pos.dir) * speed[1];
        _wm->ourRobot[i].vel2.dir = speed[2];
    }
    //_wm->ourRobot[0].vel = _wm->ourRobot[0].vel2;
    //qDebug() << _wm->ourRobot[0].vel2.loc.length()<<","<<_wm->ourRobot[0].vel.loc.length();
    //qDebug() << _wm->ourRobot[0].vel2.dir;
}
