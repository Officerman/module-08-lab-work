#include <iostream>
using namespace std;

// Интерфейс команды
class ICommand {
public:
    virtual void Execute() = 0;
    virtual void Undo() = 0;
    virtual ~ICommand() = default;
};

// Устройства
class Light {
public:
    void On() { cout << "Light is On" << endl; }
    void Off() { cout << "Light is Off" << endl; }
};

class Door {
public:
    void Open() { cout << "Door is Open" << endl; }
    void Close() { cout << "Door is Closed" << endl; }
};

class Thermostat {
private:
    int temp = 20;
public:
    void Increase() { cout << "Temperature: " << ++temp << " degrees" << endl; }
    void Decrease() { cout << "Temperature: " << --temp << " degrees" << endl; }
};

// Реализация команд
class LightOnCommand : public ICommand {
    Light& device;
public:
    LightOnCommand(Light& dev) : device(dev) {}
    void Execute() override { device.On(); }
    void Undo() override { device.Off(); }
};

class LightOffCommand : public ICommand {
    Light& device;
public:
    LightOffCommand(Light& dev) : device(dev) {}
    void Execute() override { device.Off(); }
    void Undo() override { device.On(); }
};

class DoorOpenCommand : public ICommand {
    Door& device;
public:
    DoorOpenCommand(Door& dev) : device(dev) {}
    void Execute() override { device.Open(); }
    void Undo() override { device.Close(); }
};

class DoorCloseCommand : public ICommand {
    Door& device;
public:
    DoorCloseCommand(Door& dev) : device(dev) {}
    void Execute() override { device.Close(); }
    void Undo() override { device.Open(); }
};

class IncreaseTempCommand : public ICommand {
    Thermostat& device;
public:
    IncreaseTempCommand(Thermostat& dev) : device(dev) {}
    void Execute() override { device.Increase(); }
    void Undo() override { device.Decrease(); }
};

class DecreaseTempCommand : public ICommand {
    Thermostat& device;
public:
    DecreaseTempCommand(Thermostat& dev) : device(dev) {}
    void Execute() override { device.Decrease(); }
    void Undo() override { device.Increase(); }
};

// Класс Invoker
class RemoteControl {
    ICommand* lastCommand = nullptr;
public:
    void SetCommand(ICommand* command) {
        lastCommand = command;
        lastCommand->Execute();
    }

    void UndoLastCommand() {
        if (lastCommand) lastCommand->Undo();
    }
};

// Клиентский код
int main() {
    // Создание устройства
    Light light;
    Door door;
    Thermostat thermostat;

    // Создаем команды для управления устройствами
    LightOnCommand lightOn(light);
    LightOffCommand lightOff(light);
    DoorOpenCommand doorOpen(door);
    DoorCloseCommand doorClose(door);
    IncreaseTempCommand tempUp(thermostat);
    DecreaseTempCommand tempDown(thermostat);

    // Пульт управления
    RemoteControl remote;

    // Управление устройствами
    remote.SetCommand(&lightOn);
    remote.SetCommand(&lightOff);
    remote.UndoLastCommand();

    remote.SetCommand(&doorOpen);
    remote.SetCommand(&doorClose);
    remote.UndoLastCommand();

    remote.SetCommand(&tempUp);
    remote.SetCommand(&tempDown);
    remote.UndoLastCommand();

    return 0;
}
