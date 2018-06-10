//
//  message_plat_test.cpp
//
//  Created by Tejas Harith on 6/5/18.
//  Copyright © 2018 Tejas Harith. All rights reserved.
//

#include <stdio.h>
#include <iostream>
//#include "MessagingPlatform/OnValChanged.h"

class TestEvent
{
    unsigned int id = 30001;
};

enum simpleState
{
    OFF = 0,
    ON = 1,
    OTHER = 2,
    TEST = 3
};

class RecipientA
{
    simpleState my_state = simpleState::OFF;
    
public:
    void eventHandler(TestEvent e) {
        my_state = simpleState::ON;
        std::cout << "in REC_A eventHandle" << std::endl;
    }
};

class RecipientB
{
    simpleState my_state = simpleState::OFF;
    
public:
    void eventHandler(TestEvent e) {
        my_state = simpleState::ON;
        std::cout << "in REC_B eventHandle" << std::endl;
    }
};

class RecipientC
{
    simpleState my_state = simpleState::OFF;
    
public:
    void eventHandler(TestEvent e) {
        my_state = simpleState::ON;
        std::cout << "in REC_C eventHandle" << std::endl;
    }
};

class SendAndRec;

union{
    void * holder_ptr;
    RecipientA * rec_a;
    RecipientB * rec_b;
    RecipientC * rec_c;
    SendAndRec * sar;
} u2;

struct Ptr_Type_Storage {
    enum ptr_type {REC_A, REC_B, REC_C, SAR};
    
    static void load_ptr(void * ptr){
        u2.holder_ptr = ptr;
    }
    static void call_event_handle(ptr_type type, TestEvent e);
    static void call_unsubscribe(ptr_type type, void* to_unsub);
};

class Sender
{
    simpleState send_state = simpleState::OFF;
    void* subsList[10];
    Ptr_Type_Storage::ptr_type subsTypes[10];
    int subsCount = 0;
    
public:
    void set_state(simpleState s){
        send_state = s;
        publishEvent(TestEvent());
    }
    
    void subscribe(void* obj_ptr, Ptr_Type_Storage::ptr_type ptType){
        subsList[subsCount] = obj_ptr;
        subsTypes[subsCount] = ptType;
        ++subsCount;
    }
private:
    void publishEvent( TestEvent e){
        std::cout << "publishing event to all subs" << std::endl;
        for(int i = 0; i < subsCount; ++i){
            Ptr_Type_Storage::load_ptr(subsList[i]);
            Ptr_Type_Storage::call_event_handle(subsTypes[i], e);
        }
    }
};

class SendAndRec
{
    simpleState state = simpleState::OFF;
    void* subsList[10];
    Ptr_Type_Storage::ptr_type subsTypes[10];
    unsigned int subsCount = 0;
    
    void* subscriptions[10];
    Ptr_Type_Storage::ptr_type subscriptionTypes[10];
    unsigned int subscriptionsCount = 0;
    
public:
    void eventHandler(TestEvent e) {
        state = simpleState::ON;
        std::cout << "in Send_and_rec eventHandle" << std::endl;
    }
    template <typename T>
    void subscribe(T* obj_ptr, Ptr_Type_Storage::ptr_type ptType){
        obj_ptr->addSubscription(this, Ptr_Type_Storage::ptr_type::SAR);
        subsList[subsCount] = (void*)obj_ptr;
        subsTypes[subsCount] = ptType;
        ++subsCount;
    }
    void unsubscribe(void* remove_this){
        std::cout << "unsubscribing this pointer" << std::endl;
    }
    
    void set_state(simpleState s){
        state = s;
        publishEvent(TestEvent());
    }
    std::string get_state(){
        return std::to_string(state);
    }
    void addSubscription(void* pub_obj_ptr, Ptr_Type_Storage::ptr_type ptType){
        subscriptions[subscriptionsCount] = pub_obj_ptr;
        subscriptionTypes[subscriptionsCount] = ptType;
        ++subscriptionsCount;
    }
    ~SendAndRec(){
        for(int i = 0; i < subscriptionsCount; ++i){
            Ptr_Type_Storage::load_ptr(subscriptions[i]);
            Ptr_Type_Storage::call_unsubscribe(subscriptionTypes[i], this);
        }
    }
private:
    void publishEvent( TestEvent e){
        std::cout << "publishing event to all subs" << std::endl;
        for(int i = 0; i < subsCount; ++i){
            Ptr_Type_Storage::load_ptr(subsList[i]);
            Ptr_Type_Storage::call_event_handle(subsTypes[i], e);
        }
    }
};

void Ptr_Type_Storage::call_event_handle(ptr_type type, TestEvent e){
    std::cout << "in ptr_type_storage call_event_Handle" << std::endl;
    switch(type){
        case ptr_type::REC_A:
            u2.rec_a->eventHandler(e);
            break;
        case ptr_type::REC_B:
            u2.rec_b->eventHandler(e);
            break;
        case ptr_type::REC_C:
            u2.rec_c->eventHandler(e);
            break;
        case ptr_type::SAR:
            u2.sar->eventHandler(e);
            break;
        default:
            std::cout << "type not found " << std::endl;
            
    }
}

void Ptr_Type_Storage::call_unsubscribe(ptr_type type, void* to_unsub){
    std::cout << "in ptr_type_storage call_unsub" << std::endl;
    switch(type){
//        case ptr_type::REC_A:
//            u2.rec_a->unsubscribe(to_unsub);
//            break;
//        case ptr_type::REC_B:
//            u2.rec_b->unsubscribe(to_unsub);
//            break;
//        case ptr_type::REC_C:
//            u2.rec_c->unsubscribe(to_unsub);
//            break;
        case ptr_type::SAR:
            u2.sar->unsubscribe(to_unsub);
            break;
        default:
            std::cout << "type not found " << std::endl;
            
    }
}

//
//struct sameS{
//    int x = 5;
//    typedef void (sameS::*ssfs) (int);
//    ssfs su = &sameS::set_state_from_struc;
//    void set_state_from_struc(int a1){
//        //do something
//        std::cout << "in here, but shouldnt be" << std::endl;
//    }
//};
//
//
//
//class StateChangeEvent
//{
//private:
//
//public:
//    int id= 3001;
//};
//
//class Class1
//{
//
//private:
//    simpleState state;
//
//public:
////    friend struct S;
//    Class1()
//    :s1(*this){
////        s1 = S(*this);
//    }
//
//    struct S{
//        int x = 47;
//        S(Class1 & c)
//        :parent(c){
//
//        }
//        Class1& parent;
//        typedef void (S::*ssfs) ();
//        ssfs su = &S::set_state_from_struc;
//        void set_state_from_struc(){
//            std::cout << "hehe, snuck in here, you win!" << std::endl;
//            parent.set_state(simpleState::ON);
//        }
//    };
//    S s1;
//    Class1 * self = this;
//    Class1* c5;
//    OnValChanged onStateChange;
//    void half_check(){
//        c5 = new Class1();
//    }
//    void set_state(simpleState st)
//    {
//
//        state = st;
////        onStateChange( this, StateChangeEvent() );
//    }
//    void eventHandler(int s, int e){
//        //do no
//        std::cout << "class1" <<std::endl;
//        int bo = s + e;
//        std::cout << bo << std::endl;
//        //        switch(e.id){
//        //            case 3001:
//        //                state = simpleState::ON;
//        //                break;
//        //            default:
//        //                std::cout << "test" << std::endl
//    }
//    std::string get_state()
//    {
//        std::string g = std::to_string(state);
//        return g;
//    }
//};
//
//class Class2
//{
//private:
//    simpleState state;
//
//public:
//    Class2()
//    {
//        state = simpleState::OFF;
//    }
//    union{
//        struct{
//            int p = 4;
//            void gweq(){
//                std::cout << "in gweq" << std::endl;
//            }
//        } s21;
//        struct{
//            int q;
//            void gwel(){};
//        } s22;
//    };
////    template <typename Send, typename Eve>
//    void eventHandler(int s, int e){
//        //do no
//        int bo = s + e;
//        std::cout << bo << std::endl;
////        switch(e.id){
////            case 3001:
////                state = simpleState::ON;
////                break;
////            default:
////                std::cout << "test" << std::endl
//    }
//
//    void doSomethur(Class1* cla1){
//        //do no
//        cla1->set_state(simpleState::ON);
//    }
//    std::string get_state()
//    {
//        std::string g = std::to_string(state);
//        return g;
//    }
//
//};
//
int main()
{
    //    RecipientA ra1;
    //    RecipientB rb1;
    //    RecipientC rc1;
    //    Sender s1;
    //    Sender s2;
    //    Sender s3;
    
    SendAndRec sar1;
    SendAndRec sar2;
    
    //    s1.subscribe(&ra1, Ptr_Type_Storage::REC_A);
    //    s1.subscribe(&rb1, Ptr_Type_Storage::REC_B);
    //    s1.subscribe(&rc1, Ptr_Type_Storage::REC_C);
    //
    //    s2.subscribe(&rb1, Ptr_Type_Storage::REC_B);
    //    s1.set_state(simpleState::ON);
    //    s2.set_state(simpleState::ON);
    //
    //    s3.set_state(simpleState::ON);
    
    std::cout << sar1.get_state() << std::endl;
    std::cout << sar2.get_state() << std::endl;
    sar1.subscribe<SendAndRec>(&sar2, Ptr_Type_Storage::SAR);
    
    sar1.set_state(simpleState::ON);
    std::cout << sar1.get_state() << std::endl;
    std::cout << sar2.get_state() << std::endl;
    
    //    Class1 c1;
    //    Class1 c3;
    //    Class2 c2;
    //    c1.set_state(simpleState::OFF);
    //    c3.set_state(simpleState::OFF);
    //    Class1 * cptr = c1.self;
    ////    int c = 4;
    ////    int * ipr = &c;
    ////    c1.half_check();
    ////    std::cout << c1.c5->get_state() << std::endl;
    ////    c2.doSomethur(c1.c5);
    ////    std::cout << c1.c5->get_state() << std::endl;
    //
    ////    void * glux = cptr;
    ////    Class1 ** tp = (Class1**)glux;
    ////    std::cout << (*(*tp)).get_state() << std::endl;
    //
    ////    unsigned char a = *(char*)tp;
    ////    std::cout << sizeof(a) << " and : " << std::to_string(a) << " yea" << std::endl;
    //    std::cout << c1.get_state() << std::endl;
    //    std::cout << c3.get_state() << std::endl;
    //    cptr->set_state(simpleState::ON);
    //    std::cout << c1.get_state() << std::endl;
    //    std::cout << c3.get_state() << std::endl;
    //    cptr = &c3;
    //    cptr->set_state(simpleState::ON);
    //    std::cout << c1.get_state() << std::endl;
    //    std::cout << c3.get_state() << std::endl;
    //
    //    std::cout << "+++++++++++++" <<std::endl;
    ////    sameS* s_ptr;
    ////    Class1::S * sss_ptr = &c1.s1;
    ////    s_ptr = (sameS*)sss_ptr;
    ////    std::cout << s_ptr->x << std::endl;
    ////    auto glip = s_ptr->su;
    ////    std::cout <<  << std::endl;
    //    c2.s22.gwel();
    //////    int ge = glip;
    ////    std:: cout << *glip << std::endl;
    ////    std::cout << typeof(glip) << std::endl;
    //    // do somethign
    //
    //
    ////    void ( * const click) ( Class1 s, StateChangeEvent e ) = &Class2::eventHandler<Class1, StateChangeEvent>;
    ////    c1.onStateChange.subscribe<Class2>(c2);
    ////    c1.onStateChange.subscribe<Class1>(c3);
    ////    c1.set_state(ON);
    //////    int j = 1;
    //////        int g = c1.onStateChange.simples(j);
    //////    std::cout << g << std::endl;
    ////    std::cout << c2.get_state() << std::endl;
}
