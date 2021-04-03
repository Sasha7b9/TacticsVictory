// 2021/04/02 17:14:22 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by


int main()
{
    setlocale(LC_ALL, "Russian");

    LogRAW::Create("Uploader.log");

    LOGWRITE("Start Uploader");

    TheConfig.Load("Uploader.cfg");

    TheMaster.Connect(TheConfig.GetStringValue("address master"));

    return 0;
}
