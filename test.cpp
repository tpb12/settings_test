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
#define UNPACK_ALL TRUE 
#define MARK_ALL FALSE
#define STATUS_PERIOD 77
#define SEND_STATUS_TO 11
#define COMPOSED_MASK_DEST 0x0008
#define COMPOSED_MASK_SRC 0x0009
#define MASK_DEST 0x0010
#define MASK_SRC 0x000A
#define TU_TYPE 0x000003
#define TU_SRC_MASK 0x0001
#define TU_SRC_COM_INDEX TRUE
#define TU_PRIM_TO_SEC 2
#define TU_SEC_TO_PRIMK 3
#define KEEP_LOG FALSE
#define LOG_COMPOSED_TYPE 0x0006
#define LOG_PACK_ALL FALSE
#define LOG_UNPACK_ALL TRUE
#define LOG_COMPOSED_TYPE_TO_PACK 0x0007
#define SOURCE_ID 0x000021
#define STATUS_REQUEST_MESSAGE_TYPE 0x0003
#define STATUS_DATA_0 11
#define STATUS_DATA_1 22

void FillMapWordToPtr(CSettings::MapWordToPtr& map)
{
    map.clear();
    map.insert({ (WORD)0x100, NULL });
    map.insert({ (WORD)0x200, NULL });
    map.insert({ (WORD)0x300, NULL });
}

BOOL CheckMapWordToPtr(const CSettings::MapWordToPtr& map)
{
    /*POSITION pos = map.GetStartPosition();
    while (pos != NULL)
    {
        WORD wType;
        void* pTemp;
        map.GetNextAssoc(pos, wType, pTemp);
        CString str;
        str.Format(_T("%04X "), wType);
        std::cout << "map = " << str.GetBuffer() << std::endl;
    }*/
    return TRUE;
}

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

        //CByteArray arTemp;
        ByteArrayFromString(PREFIX, g_Settings.m_arPrefix, _T(""));
        //g_Settings.m_arPrefix.Copy(arTemp);
        ByteArrayFromString(OUT_PREFIX, g_Settings.m_arOutPrefix, _T(""));
        //g_Settings.m_arOutPrefix.Copy(arTemp);

        g_Settings.m_wComposedType = COMPOSED_TYPE;
        g_Settings.m_wOutputComposedType = OUTPUT_COMPOSED_TYPE;
        g_Settings.m_wCRC16Init = CRC16_INIT;
        g_Settings.m_wCPAddr = CP_ADDR;
        g_Settings.m_wPUAddr = PU_ADDR;

        g_Settings.m_bUnpackAll = UNPACK_ALL;
        g_Settings.m_bMarkAll = MARK_ALL;
        FillMapWordToPtr(g_Settings.m_mapMsgTypesToMark);

        g_Settings.m_nStatusPeriod = STATUS_PERIOD;
        g_Settings.m_iSendStatTO = SEND_STATUS_TO;

        g_Settings.m_MarkComposedMask = CSettings::MESSAGETYPE();
        g_Settings.m_MarkComposedMask.m_wDestMask = COMPOSED_MASK_DEST;
        g_Settings.m_MarkComposedMask.m_wSrcMask = COMPOSED_MASK_SRC;

        g_Settings.m_MarkNestedMask = CSettings::MESSAGETYPE();
        g_Settings.m_MarkNestedMask.m_wDestMask = MASK_DEST;
        g_Settings.m_MarkNestedMask.m_wSrcMask = MASK_SRC;

        //***
        g_Settings.m_mapMsgTypes.clear();
        CSettings::MESSAGETYPE typeStatus(0x0007, 0x1008);
        //g_Settings.m_mapMsgTypes.SetAt(0x0001, typeStatus);
        g_Settings.m_mapMsgTypes.insert({ 0x0001, typeStatus });
        CSettings::MESSAGETYPE typeStatus1(0x0008, 0x1009);
        //g_Settings.m_mapMsgTypes.SetAt(0x0002, typeStatus1);
        g_Settings.m_mapMsgTypes.insert({ 0x0002, typeStatus1 });

        //***
        g_Settings.m_StatusHdr = CSettings::MESSAGETYPE(0x0000, 0x20);
        g_Settings.m_StatusMsg =
            CSettings::MESSAGETYPE(g_Settings.m_wComposedType);

        g_Settings.m_TUType = TU_TYPE;
        g_Settings.m_TUSrcMask = TU_SRC_MASK;
        g_Settings.m_TUSrcComMsgIndex = TU_SRC_COM_INDEX;
        g_Settings.m_TUPrimToSecSrc = TU_PRIM_TO_SEC;
        g_Settings.m_TUSecToPrimSrc = TU_SEC_TO_PRIMK;

        g_Settings.m_bKeepLog = KEEP_LOG;
        g_Settings.m_wLogComposedType = LOG_COMPOSED_TYPE;
        g_Settings.m_bLogPackAll = LOG_PACK_ALL;

        g_Settings.m_wLogComposedTypeToPack = LOG_COMPOSED_TYPE_TO_PACK;
        g_Settings.m_bLogUnpackAll = LOG_UNPACK_ALL;

        g_Settings.m_wSourceID = SOURCE_ID;
        g_Settings.m_wStatusRequestMessageType = STATUS_REQUEST_MESSAGE_TYPE;

        g_Settings.m_arStatusData.resize(2);
        g_Settings.m_arStatusData[0] = STATUS_DATA_0;
        g_Settings.m_arStatusData[1] = STATUS_DATA_1;
    }
    ~TestSettings() { }
    void SetUp() { }
    void TearDown() { }

protected:
};

void t1()
{
    BOOL res = g_Settings.Save(SET_FILE_NAME);
    EXPECT_TRUE(res);
    CSettings local_settings;
    res = local_settings.Load(SET_FILE_NAME);
    EXPECT_TRUE(res);
    //local_settings.MakeStatusMsg();

    EXPECT_EQ(local_settings.m_dwPollingPeriod, POLLING_PERIOD);
    EXPECT_EQ(local_settings.m_bTestLoopback, TEST_LOOPBACK);
    EXPECT_EQ(local_settings.m_bShowSIOMessages, SHOW_SID_MESSAGE);
    EXPECT_EQ(local_settings.m_bShowMessageErrors, SHOW_MESSAGE_ERRORS);
    EXPECT_EQ(local_settings.m_bShowCOMErrors, SHOW_COM_ERRORS);

    ASSERT_STREQ(local_settings.m_strSettingsReportPath.c_str(), SETTINGS_REPORT_PATH);

    EXPECT_EQ(local_settings.m_nBufferSize, BUFFER_SIZE);
    EXPECT_EQ(local_settings.m_nIncomingPort, INCOMING_PORT);
    ASSERT_STREQ(local_settings.m_strCOMSetup.c_str(), COM_SETUP);

    ASSERT_EQ(local_settings.m_iCOMRttc, COM_RTTC);
    ASSERT_EQ(local_settings.m_iCOMWttc, COM_WTTC);
    ASSERT_EQ(local_settings.m_iCOMRit, COM_RIT);

    std::string strTemp;
    ByteArrayToString(local_settings.m_arPrefix,
        (int)local_settings.m_arPrefix.size(), strTemp, "");
    ASSERT_STREQ(strTemp.c_str(), PREFIX);
    ByteArrayToString(local_settings.m_arOutPrefix,
        (int)local_settings.m_arOutPrefix.size(), strTemp, "");
    ASSERT_STREQ(strTemp.c_str(), OUT_PREFIX);

    ASSERT_EQ(local_settings.m_wComposedType, COMPOSED_TYPE);
    ASSERT_EQ(local_settings.m_wOutputComposedType, OUTPUT_COMPOSED_TYPE);
    ASSERT_EQ(local_settings.m_wCRC16Init, CRC16_INIT);
    ASSERT_EQ(local_settings.m_wCPAddr, CP_ADDR);
    ASSERT_EQ(local_settings.m_wPUAddr, PU_ADDR);

    ASSERT_EQ(local_settings.m_bUnpackAll, UNPACK_ALL);
    ASSERT_EQ(local_settings.m_bMarkAll, MARK_ALL);
    res = CheckMapWordToPtr(local_settings.m_mapMsgTypesToMark);
    ASSERT_EQ(res, TRUE);

    ASSERT_EQ(local_settings.m_nStatusPeriod, STATUS_PERIOD);
    ASSERT_EQ(local_settings.m_iSendStatTO, SEND_STATUS_TO);

    ASSERT_EQ(local_settings.m_MarkComposedMask.m_wDestMask, COMPOSED_MASK_DEST);
    ASSERT_EQ(local_settings.m_MarkComposedMask.m_wSrcMask, COMPOSED_MASK_SRC);
    ASSERT_EQ(local_settings.m_MarkNestedMask.m_wDestMask, MASK_DEST);
    ASSERT_EQ(local_settings.m_MarkNestedMask.m_wSrcMask, MASK_SRC);

    // POSITION pos = local_settings.m_mapMsgTypes.GetStartPosition(); //***
    // local_settings.m_StatusHdr; //***
    // local_settings.m_StatusMsg; //***

    ASSERT_EQ(local_settings.m_TUType, TU_TYPE);
    ASSERT_EQ(local_settings.m_TUSrcMask, TU_SRC_MASK);
    ASSERT_EQ(local_settings.m_TUSrcComMsgIndex, TU_SRC_COM_INDEX);
    ASSERT_EQ(local_settings.m_TUPrimToSecSrc, TU_PRIM_TO_SEC);
    ASSERT_EQ(local_settings.m_TUSecToPrimSrc, TU_SEC_TO_PRIMK);

    ASSERT_EQ(local_settings.m_bKeepLog, KEEP_LOG);
    ASSERT_EQ(local_settings.m_wLogComposedType, LOG_COMPOSED_TYPE);
    ASSERT_EQ(local_settings.m_bLogPackAll, LOG_PACK_ALL);

    ASSERT_EQ(local_settings.m_wLogComposedTypeToPack, LOG_COMPOSED_TYPE_TO_PACK);
    ASSERT_EQ(local_settings.m_bLogUnpackAll, LOG_UNPACK_ALL);

    ASSERT_EQ(local_settings.m_wSourceID, SOURCE_ID);
    ASSERT_EQ(local_settings.m_wStatusRequestMessageType, STATUS_REQUEST_MESSAGE_TYPE);

    ASSERT_EQ(g_Settings.m_arStatusData[0], STATUS_DATA_0);
    ASSERT_EQ(g_Settings.m_arStatusData[1], STATUS_DATA_1);
    //EXPECT_TRUE(true);
}

TEST_F(TestSettings, Test)
{
    t1();
}
