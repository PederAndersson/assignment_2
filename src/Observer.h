//
// Created by peder on 2025-11-14.
//

#ifndef ASSIGNMENT_2_OBSERVER_H
#define ASSIGNMENT_2_OBSERVER_H
struct Measurement;

struct MinMax {
    float upper_{};
    float lower_{};
};
class IObserver {
protected:
    MinMax value_;//value to check against
    bool check_upper_ = false; // if true active
    bool check_lower_ = false;
public:
    virtual ~IObserver() = default;
    virtual void ifBreachedNotify(const Measurement& m) = 0;
    virtual void checkValue(const Measurement& m, const float & value) = 0;
    [[nodiscard]] virtual MinMax getThreshold() const = 0;
    virtual void setThreshold() = 0;

};

enum class Bound {
    upper = 1,
    lower
};

class ThresholdObserver : public IObserver {
private:

public:
    ThresholdObserver() = default;
    ThresholdObserver(float upper, float lower) {
        value_.upper_ = upper;
        value_.lower_ = lower;
        check_lower_ = true;
        check_upper_ = true;
    }

    ThresholdObserver(float value, Bound bound) {
        switch (bound) {
            case Bound::upper: {
                value_.upper_ = value;
                check_upper_ = true;
                break;
            }
            case Bound::lower: {
                value_.lower_ = value;
                check_lower_ = true;
                break;
            }
        }
    }
    void ifBreachedNotify(const Measurement& m) override;
    void checkValue(const Measurement& m, const float & value) override;
    [[nodiscard]] MinMax getThreshold() const override;
    void setThreshold() override;


};




#endif //ASSIGNMENT_2_OBSERVER_H