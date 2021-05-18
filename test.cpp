#include "stdafx.h"

#define SET_FILE_NAME "profile.dat"

#define POLLING_PERIOD 20
#define TEST_LOOPBACK TRUE
#define SHOW_SID_MESSAGE TRUE
#define SHOW_MESSAGE_ERRORS TRUE
#define SHOW_COM_ERRORS TRUE
#define SETTINGS_REPORT_PATH "test1.dat"
#define BUFFER_SIZE 0x91111
#define INCOMING_PORT 17132
#define COM_SETUP "COM2: baud=9600 data=8 parity=N stop=0"
#define COM_RTTC 0
#define COM_WTTC 1
#define COM_RIT -2
#define PREFIX "11"
#define OUT_PREFIX "22"
#define COMPOSED_TYPE 0x0003
#define OUTPUT_COMPOSED_TYPE 0x0004
#define CRC16_INIT 0xFFFF
#define CP_ADDR 0x0005
#define PU_ADDR 0x0006
#define UNPACK_ALL FALSE 
#define MARK_ALL FALSE

class TestSettings : public ::testing::Test {
public:
    TestSettings()
    {
        g_Settings.m_dwPollingPeriod = POLLING_PERIOD;
        g_Settings.m_bTestLoopback = TEST_LOOPBACK;
        g_Settings.m_bShowSIOMessages = SHOW_SID_MESSAGE;
        g_Settings.m_bShowMessageErrors = SHOW_MESSAGE_ERRORS;
        g_Settings.m_bShowCOMErrors = SHOW_COM_ERRORS;

        g_Settings.m_strSettingsReportPath = SETTINGS_REPORT_PATH;

        g_Settings.m_nBufferSize = BUFFER_SIZE;
        g_Settings.m_nIncomingPort = INCOMING_PORT;
        g_Settings.m_strCOMSetup = COM_SETUP;

        g_Settings.m_iCOMRttc = COM_RTTC;
        g_Settings.m_iCOMWttc = COM_WTTC;
        g_Settings.m_iCOMRit = COM_RIT;

        CByteArray arTemp;
        ByteArrayFromString(PREFIX, arTemp, _T(""));
        g_Settings.m_arPrefix.Copy(arTemp);
        ByteArrayFromString(OUT_PREFIX, arTemp, _T(""));
        g_Settings.m_arOutPrefix.Copy(arTemp);

        g_Settings.m_wComposedType = COMPOSED_TYPE;
        g_Settings.m_wOutputComposedType = OUTPUT_COMPOSED_TYPE;
        g_Settings.m_wCRC16Init = CRC16_INIT;
        g_Settings.m_wCPAddr = CP_ADDR;
        g_Settings.m_wPUAddr = PU_ADDR;

        g_Settings.m_bUnpackAll = UNPACK_ALL;
        g_Settings.m_bMarkAll = MARK_ALL;
    }
    ~TestSettings() { }
    void SetUp() { }
    void TearDown() { }

protected:
};

void t1()
{
    g_Settings.Save(SET_FILE_NAME);
    g_Settings.Load(SET_FILE_NAME);
    //g_Settings.MakeStatusMsg();

    EXPECT_EQ(g_Settings.m_dwPollingPeriod, POLLING_PERIOD);
    EXPECT_EQ(g_Settings.m_bTestLoopback, TEST_LOOPBACK);
    EXPECT_EQ(g_Settings.m_bShowSIOMessages, SHOW_SID_MESSAGE);
    EXPECT_EQ(g_Settings.m_bShowMessageErrors, SHOW_MESSAGE_ERRORS);
    EXPECT_EQ(g_Settings.m_bShowCOMErrors, SHOW_COM_ERRORS);

    ASSERT_STREQ(g_Settings.m_strSettingsReportPath, SETTINGS_REPORT_PATH);

    EXPECT_EQ(g_Settings.m_nBufferSize, BUFFER_SIZE);
    EXPECT_EQ(g_Settings.m_nIncomingPort, INCOMING_PORT);
    ASSERT_STREQ(g_Settings.m_strCOMSetup, COM_SETUP);

    ASSERT_EQ(g_Settings.m_iCOMRttc, COM_RTTC);
    ASSERT_EQ(g_Settings.m_iCOMWttc, COM_WTTC);
    ASSERT_EQ(g_Settings.m_iCOMRit, COM_RIT);

    CString strTemp;
    ByteArrayToString(g_Settings.m_arPrefix.GetData(),
        (int)g_Settings.m_arPrefix.GetSize(), strTemp, "");
    ASSERT_STREQ(strTemp, PREFIX);
    ByteArrayToString(g_Settings.m_arOutPrefix.GetData(),
        (int)g_Settings.m_arOutPrefix.GetSize(), strTemp, "");
    ASSERT_STREQ(strTemp, OUT_PREFIX);

    ASSERT_EQ(g_Settings.m_wComposedType, COMPOSED_TYPE);
    ASSERT_EQ(g_Settings.m_wOutputComposedType, OUTPUT_COMPOSED_TYPE);
    ASSERT_EQ(g_Settings.m_wCRC16Init, CRC16_INIT);
    ASSERT_EQ(g_Settings.m_wCPAddr, CP_ADDR);
    ASSERT_EQ(g_Settings.m_wPUAddr, PU_ADDR);

    ASSERT_EQ(g_Settings.m_bUnpackAll, UNPACK_ALL);
    ASSERT_EQ(g_Settings.m_bMarkAll, MARK_ALL);
    //EXPECT_TRUE(true);
}

TEST_F(TestSettings, Test)
{
    t1();
}
