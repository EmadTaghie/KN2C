#include "wpacket.h"

WPacket::WPacket()
{
}

void WPacket::Clear()
{
    _rdata.clear();
}

void WPacket::AddRobot(RobotData rd)
{
    //rd.RID = htons(rd.RID); // RID was 2 bytes before
    //_rdata.append(rd);
    _rdata[rd.RID]=rd;
}
//@mparchin: chnage for new WB
QByteArray WPacket::getPacketNewWB()
{
    QByteArray rd,ret;

    for(int i=0; i<_rdata.size(); i++)
    {
        if (_rdata[i].RID != 0xFF)
        {
            _rdata[i].Vx_sp = qToBigEndian<unsigned short int>(_rdata[i].Vx_sp);
            _rdata[i].Vy_sp = qToBigEndian<unsigned short int>(_rdata[i].Vy_sp);
            _rdata[i].Wr_sp = qToBigEndian<unsigned short int>(_rdata[i].Wr_sp);
            _rdata[i].Vx    = qToBigEndian<unsigned short int>(_rdata[i].Vx);
            _rdata[i].Vy    = qToBigEndian<unsigned short int>(_rdata[i].Vy);
            _rdata[i].Wr    = qToBigEndian<unsigned short int>(_rdata[i].Wr);
            _rdata[i].alpha = qToBigEndian<unsigned short int>(_rdata[i].alpha);
            //if (_rdata[i].RID == 0x01)
            //    _rdata[i].alpha = qToBigEndian<unsigned short int>(120);
            rd.append((const char*)&(_rdata[i]), 18); //sizeof(RobotData);
            ret.append(START_BYTE);
            ret.append(WRITE_REQUEST);
            ret.append((const char*)&(_rdata[i].RID),1);
            ret.append(END_BYTE);
            ret.append(START_BYTE);
            ret.append(DATA_REQUEST);
            ret.append(rd);
            ret.append(END_BYTE);
        }
    }
    Clear();
    qDebug() << ret.toHex()<<endl;
    return ret;

}

QByteArray WPacket::GetPacket()
{
    QByteArray rd;

    for(int i=0; i<_rdata.size(); i++)
    {
        _rdata[i].Vx_sp = qToBigEndian<unsigned short int>(_rdata[i].Vx_sp);
        _rdata[i].Vy_sp = qToBigEndian<unsigned short int>(_rdata[i].Vy_sp);
        _rdata[i].Wr_sp = qToBigEndian<unsigned short int>(_rdata[i].Wr_sp);
        _rdata[i].Vx    = qToBigEndian<unsigned short int>(_rdata[i].Vx);
        _rdata[i].Vy    = qToBigEndian<unsigned short int>(_rdata[i].Vy);
        _rdata[i].Wr    = qToBigEndian<unsigned short int>(_rdata[i].Wr);
        _rdata[i].alpha = qToBigEndian<unsigned short int>(_rdata[i].alpha);
        rd.append((const char*)&(_rdata[i]), 18); //sizeof(RobotData);
    }

    unsigned char checksum=0;
    for(int i=0; i<rd.size(); ++i)
        checksum += rd.at(i);

    SendPacketHeader h;
    h.SIB = (2 + 1 + 1) + rd.size() + 1; //RobotData size + 3 byte packet header + 2 byte SOP + 1 byte EOP
    h.CHK = checksum;

    QByteArray ans;
    ans.append(WP_SOP);
    ans.append((const char*)&h, 2); //sizeof(h));
    ans.append(rd);
    ans.append(WP_EOP);

    //qDebug() << ans.toHex();

    // !!!
    Clear();
    return ans;
}
