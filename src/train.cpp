// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() : countOp(0), first(nullptr) {}

Train::~Train() {
    if (!first) return;
    Car *current = first;
    do {
        Car *nextCar = current->next;
        delete current;
        current = nextCar;
    } while (current != first);
}

void Train::addCar(bool light) {
    Car *newCar = new Car{light, nullptr, nullptr};
    if (!first) {
        first = newCar;
        first->next = first;
        first->prev = first;
    } else {
        Car *last = first->prev;
        last->next = newCar;
        newCar->prev = last;
        newCar->next = first;
        first->prev = newCar;
    }
}

int Train::getLength() {
    if (!first) return 0;
    countOp = 0;
    first->light = true;
    Car *current = first;
    
    while (true) {
        int steps = 0;
        do {
            current = current->next;
            countOp++;
            steps++;
        } while (!current->light);
        
        current->light = false;
        
        for (int i = 0; i < steps; i++) {
            current = current->prev;
            countOp++;
        }
        
        if (!current->light) {
            return steps;
        }
    }
}

int Train::getOpCount() {
    return countOp;
}
