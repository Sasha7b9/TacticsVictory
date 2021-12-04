// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace Pi
{

    template <class keyType, class valueType>
    class MapByKey {
    
    public:
        MapByKey() {};
    
        bool IsExist(keyType key) {
            for (keyType &element : keys) {
                if (element == key) {
                    return true;
                }
            }
            return false;
        }
    
        void Insert(keyType key, valueType value) {
            if (IsExist(key)) {
                return;
            }
            keys.AddElement(key);
            values.AddElement(value);
        }
    
        valueType GetElement(keyType key) {
            size_t index = 0;
            for (keyType &element : keys) {
                if (element == key) {
                    break;
                }
                index++;
            }
            return values[index];
        }
    
    private:
        Array<keyType> keys;
        Array<valueType> values;
    };

}
