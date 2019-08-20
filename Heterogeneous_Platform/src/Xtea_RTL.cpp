#include "Xtea_RTL.hpp"

void Xtea_RTL::fsm()
{
    NEXT_STATUS = STATUS;
    switch (STATUS)
    {
    case START:
        NEXT_STATUS = IDLE;
        break;
    case IDLE:
        if (din_rdy.read() == 1)
        {
            NEXT_STATUS = FETCH;
        }
        else
            NEXT_STATUS = IDLE;
        break;
    case FETCH:
        if (mode.read() == 0)
            NEXT_STATUS = CFR_WORD_1;
        else if (mode.read() == 1)
            NEXT_STATUS = DECFR;
        break;
    case CFR_WORD_1:
        NEXT_STATUS = CFR_WORD_2;
        break;
    case CFR_WORD_2:
        if (counter.read() == 31)
            NEXT_STATUS = END;
        else
            NEXT_STATUS = CFR_WORD_1;
        break;
    case DECFR:
        NEXT_STATUS = DCF_WORD_1;
        break;
    case DCF_WORD_1:
        NEXT_STATUS = DCF_WORD_2;
        break;
    case DCF_WORD_2:
        if (counter.read() == 31)
            NEXT_STATUS = END;
        else
            NEXT_STATUS = DCF_WORD_1;
        break;
    case END:
        NEXT_STATUS = IDLE;
        break;
    }
}

void Xtea_RTL::datapath()
{
    if (reset.read() == 1)
    {
        STATUS = START;
    }
    else if (clock.read() == 1)
    {
        STATUS = NEXT_STATUS;
        switch (STATUS)
        {
        case START:
            dout_rdy.write(0);
            word0_pr.write(0);
            word1_pr.write(0);
            delta.write(0x9e3779b9);
            val1.write(0);
            val2.write(0);
            break;
        case IDLE:
            dout_rdy.write(0);
            // word0_pr.write(0);
            // word1_pr.write(0);
            sum.write(0);
            counter.write(0);
            val1.write(0);
            val2.write(0);
            break;
        case FETCH:
            val1.write(word0.read());
            val2.write(word1.read());
            k1.write(key1.read());
            k2.write(key2.read());
            k3.write(key3.read());
            k4.write(key4.read());
            break;
        case CFR_WORD_1:
            if ((sum.read() & 3) == 0)
                val1.write(val1.read() + ((((val2.read() << 4) ^ (val2.read() >> 5)) +
                                           val2.read()) ^
                                          (sum.read() + k1.read())));
            else if ((sum.read() & 3) == 1)
                val1.write(val1.read() + (((((val2.read() << 4) ^ (val2.read() >> 5)) +
                                            val2.read()) ^
                                           (sum.read() + k2.read()))));
            else if ((sum.read() & 3) == 2)
                val1.write(val1.read() + ((((val2.read() << 4) ^ (val2.read() >> 5)) +
                                           val2.read()) ^
                                          (sum.read() + k3.read())));
            else
                val1.write(val1.read() + ((((val2.read() << 4) ^ (val2.read() >> 5)) +
                                           val2.read()) ^
                                          (sum.read() + k4.read())));
            sum.write(sum.read() + delta.read());
            break;
        case CFR_WORD_2:
            if ((sum.read() >> 11 & 3) == 0)
                val2.write(val2.read() + ((((val1.read() << 4) ^ (val1.read() >> 5)) +
                                           val1.read()) ^
                                          (sum.read() + k1.read())));
            else if ((sum.read() >> 11 & 3) == 1)
                val2.write(val2.read() + (((((val1.read() << 4) ^ (val1.read() >> 5)) +
                                            val1.read()) ^
                                           (sum.read() + k2.read()))));
            else if ((sum.read() >> 11 & 3) == 2)
                val2.write(val2.read() + ((((val1.read() << 4) ^ (val1.read() >> 5)) +
                                           val1.read()) ^
                                          (sum.read() + k3.read())));
            else
                val2.write(val2.read() + ((((val1.read() << 4) ^ (val1.read() >> 5)) +
                                           val1.read()) ^
                                          (sum.read() + k4.read())));
            counter.write(counter.read() + 1);
            break;
        case DECFR:
            sum.write(delta.read() * 32);
            break;
        case DCF_WORD_1:
            if ((sum.read() >> 11 & 3) == 0)
                val2.write(val2.read() - ((((val1.read() << 4) ^ (val1.read() >> 5)) +
                                           val1.read()) ^
                                          (sum.read() + k1.read())));
            else if ((sum.read() >> 11 & 3) == 1)
                val2.write(val2.read() - (((((val1.read() << 4) ^ (val1.read() >> 5)) +
                                            val1.read()) ^
                                           (sum.read() + k2.read()))));
            else if ((sum.read() >> 11 & 3) == 2)
                val2.write(val2.read() - ((((val1.read() << 4) ^ (val1.read() >> 5)) +
                                           val1.read()) ^
                                          (sum.read() + k3.read())));
            else
                val2.write(val2.read() - ((((val1.read() << 4) ^ (val1.read() >> 5)) +
                                           val1.read()) ^
                                          (sum.read() + k4.read())));
            sum.write(sum.read() - delta.read());
            break;
        case DCF_WORD_2:
            if ((sum.read() & 3) == 0)
                val1.write(val1.read() - ((((val2.read() << 4) ^ (val2.read() >> 5)) +
                                           val2.read()) ^
                                          (sum.read() + k1.read())));
            else if ((sum.read() & 3) == 1)
                val1.write(val1.read() - ((((val2.read() << 4) ^ (val2.read() >> 5)) +
                                           val2.read()) ^
                                          (sum.read() + k2.read())));
            else if ((sum.read() & 3) == 2)
                val1.write(val1.read() - ((((val2.read() << 4) ^ (val2.read() >> 5)) +
                                           val2.read()) ^
                                          (sum.read() + k3.read())));
            else
                val1.write(val1.read() - ((((val2.read() << 4) ^ (val2.read() >> 5)) +
                                           val2.read()) ^
                                          (sum.read() + k4.read())));
            counter.write(counter.read() + 1);
            break;
        case END:
            word0_pr.write(val1.read());
            word1_pr.write(val2.read());
            dout_rdy.write(1);
            break;
        }
    }
}