// 2021/04/02 17:14:22 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by


int main()
{
    setlocale(LC_ALL, "Russian");

    LogRAW::Create("Controller.log");

    LOGWRITE("Start Controller");

    TheConfig.Load("Contoller.cfg");

    TheMaster.Connnect();

    return 0;
}
