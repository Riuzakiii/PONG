#pragma once
#include <string>

class Device
{
public:
    Device (const std::string& name) : name (name){};
    virtual ~Device() = default;

    virtual bool init() { return true; };
    [[nodiscard]] virtual int getState() const { return 0; };

protected:
    std::string name = "";

private:
    Device() = default;
};
