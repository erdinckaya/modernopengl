//
// Created by erdinc on 04-12-20.
//

#ifndef MODERNOPENGL_RENDERQUEUE_H
#define MODERNOPENGL_RENDERQUEUE_H

#include "../render/RenderData.h"

class RenderQueue {
    using Data = std::vector<RenderData>;
public:
    void add(Data&& data) noexcept {
        if (mIsEmpty) {
            mBuffer[(int)Order::Current] = std::move(data);
        } else {
            mBuffer[(int)Order::Next] = std::move(data);
        }
        mIsEmpty = false;
    }

    Data pop() noexcept {
        auto current = mBuffer[(int)Order::Current];
        if (!mBuffer[(int)Order::Next].empty()) {
            mBuffer[(int)Order::Current] = mBuffer[(int)Order::Next];
            mBuffer[(int)Order::Next] = {};
        }

        return current;
    }

private:
    enum class Order {
        Current = 0,
        Next = 1,
        Total = 2
    };

    bool mIsEmpty{true};
    std::array<Data, (int)Order::Total> mBuffer;
};

#endif //MODERNOPENGL_RENDERQUEUE_H
