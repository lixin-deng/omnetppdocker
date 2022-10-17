#include <string.h>
#include <omnetpp.h>
#include <bitset>

#include <iostream>
#include <fstream>

#include "MyMsg_m.h"

#include <algorithm>
#include <vector>
#include <random> // std::default_random_engine

#define _GLIBCXX_USE_CXX11_ABI 0

using namespace omnetpp;

class My_node : public cSimpleModule
{
  protected:
    // The following redefined virtual function holds the algorithm.
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};


// The module class needs to be registered with OMNeT++
Define_Module(My_node);


std::string readTxt(std::string file){
    std::ifstream infile;
    infile.open(file.data());
    assert(infile.is_open());

    std::string s;
    std::string data;
    while(getline(infile,s)){
        data = data + "NEW_LINE" +s;
    }
    infile.close();
    return data;
}


bool isFileExists_ifstream(std::string file) {
    std::ifstream f(file.data());
    return f.good();
}



std::vector<int> randperm(int Num)
{
    std::vector<int> temp;
    for (int i = 0; i < Num; i++)
    {
        temp.push_back(i);
    }
    unsigned seed = std::chrono::system_clock::now ().time_since_epoch ().count ();
    std::shuffle (temp.begin (), temp.end (), std::default_random_engine (seed));

    return temp;

}

std::vector<int> files = randperm(45);
int file_index = 0;
std::vector<int> senders;
std::vector<int> receivers;
std::vector<std::string> sources;
std::vector<std::string> outputs;


//确定receiver
//std::vector<int> receiver_ouput;

bool isFirstNode = true;

void My_node::initialize()
{
    if(isFirstNode){
        for (int i = 0; i <45; i++)
        {
            std::string textPath = "/Users/denglixin/lixin/adelaide/Y2_S2/research project/multinews/articles/source";
            std::string sourceTemp = readTxt(textPath+std::to_string(files[file_index])+".txt");
            sources.push_back(sourceTemp);
        }
    //随机生成sender和receiver
    //单数为sender 双数为receiver
    std::vector<int> nodes = randperm(49);

    EV <<  "Random numbers to generate sender and receiver:  ";
    for (int i = 0; i < nodes.size(); i++)
    {
        EV << nodes[i] << " ";
    }
    EV << " \n";

    int index_sender_receiver = 0;
    //考虑三个都为sender或者三个都为receiver的情况
    for (int i = 0; i < 3; i++)
    {
        //前两个都为sender，第三个一定为receiver
        if( senders.size() == 2){
            receivers.push_back(index_sender_receiver);
            //前两个都为receiver，第三个一定为sender
        }else if(receivers.size() == 2){
            senders.push_back(index_sender_receiver);
            //sender和receive的size都小于2，则可以继续随机
        }else {
            if(nodes[i]%5 == 0 || nodes[i]%5 == 1 || nodes[i]%5 == 2){
               senders.push_back(index_sender_receiver);
               index_sender_receiver = index_sender_receiver + 1;
            }else{
               receivers.push_back(index_sender_receiver);
               index_sender_receiver = index_sender_receiver + 1;
            }
        }
    }

    EV << "Senders size:  "<< senders.size()<< " \n";
    EV << "Receivers size:  "<< receivers.size()<< " \n";

    EV << "Senders:  ";
    for (int i = 0; i < senders.size(); i++){
        EV <<  "  node: " << senders[i] <<" ;  ";
    }
    EV << " \n";

    EV << "Receivers:  ";
    for (int i = 0; i < receivers.size(); i++){
       EV <<  "  node " << receivers[i] <<" ;  ";
    }
    EV << " \n";

    EV <<  "Random order to send files:  ";
    for (int i = 0; i < files.size(); i++){
        EV <<  "  " << files[i];
    }
    EV << " \n";
    isFirstNode = false;
    EV <<"files.size: "<<files.size()<<endl;
    EV << "Starting sending files... \n";
    }


    //senders开始发
    if(getIndex() == senders[0]){
        MyMSG *msg = new MyMSG("initial1");
        //std::string temp = readTxt(textPath+std::to_string(files[file_index])+".txt");
        std::string temp = sources[files[file_index]];
        EV << "temp file_index: "<<files[file_index]<<endl;
        const char *p = temp.data();
        msg->setData(p);
        msg->setSource(senders[0]);
        if(senders[0] == 0){
            if(receivers[0]==1){
                send(msg,"gate$o",0);
            }
            if(receivers[0]==2){
                send(msg,"gate$o",1);
            }
       }
       if(senders[0] == 1){
             if(receivers[0]==0){
                 send(msg,"gate$o",0);
             }
             if(receivers[0]==2){
                 send(msg,"gate$o",1);
             }
       }
       if(senders[0] == 2){
              if(receivers[0]==0){
                  send(msg,"gate$o",1);
              }
              if(receivers[0]==1){
                  send(msg,"gate$o",0);
              }
       }
       EV <<"file "<<file_index<<": " << files[file_index] << " send. From node:" << senders[0] <<"\n";
       file_index = file_index + 1;
    }
    if(senders.size()==2 && getIndex() == senders[1]){
    MyMSG *msg = new MyMSG("initial2");
    std::string temp = sources[files[file_index]];
    EV << "temp file_index: "<<files[file_index]<<endl;
    const char *p = temp.data();
    msg->setData(p);
    msg->setSource(senders[1]);

    if(senders[1] == 0){
        if(receivers[0]==1){
            send(msg,"gate$o",0);
        }
        if(receivers[0]==2){
            send(msg,"gate$o",1);
        }
    }
    if(senders[1] == 1){
        if(receivers[0]==0){
            send(msg,"gate$o",0);
        }
        if(receivers[0]==2){
            send(msg,"gate$o",1);
        }
    }
    if(senders[1] == 2){
        if(receivers[0]==0){
            send(msg,"gate$o",1);
        }
        if(receivers[0]==1){
            send(msg,"gate$o",0);
        }
    }
    EV <<"file "<<file_index<<": " << files[file_index] << " send. From node:" << senders[1] <<"\n";
    file_index = file_index + 1;
    }
}


void My_node::handleMessage(cMessage *msg)
{
    int source;
    std::string data;

    MyMSG *mmsg = check_and_cast<MyMSG *>(msg);
    source = mmsg->getSource();
    data = mmsg->getData();

    if (getIndex() == receivers[0]){
        if(data.size()!=0){
            outputs.push_back(data);
           // mysql_write(data);
        }
        delete msg;
        MyMSG *msg = new MyMSG("received");
        msg->setSource(receivers[0]);
        msg->setData("received!!!!");
        if(receivers[0] == 0){
            if(source == 1){
                send(msg,"gate$o",0);
            }
            if(source == 2){
                send(msg,"gate$o",1);
            }
        }
        if(receivers[0] == 1){
            if(source == 0){
                 send(msg,"gate$o",0);
            }
            if(source == 2){
                 send(msg,"gate$o",1);
            }
         }
        if(receivers[0] == 2){
            if(source == 0){
                 send(msg,"gate$o",1);
            }
            if(source == 1){
                 send(msg,"gate$o",0);
            }
         }
    }else{

        delete msg;
            if(getIndex() == senders[0]){
                if(sources.size() > file_index){
                    MyMSG *msg = new MyMSG("new1");
                    std::string temp = sources[files[file_index]];
                    EV << "temp file_index: "<<files[file_index]<<endl;
                    const char *p = temp.data();
                    msg->setData(p);
                    msg->setSource(senders[0]);
                    if(senders[0] == 0){
                        if(source == 1){
                            send(msg,"gate$o",0);
                        }
                        if(source == 2){
                            send(msg,"gate$o",1);
                        }
                    }
                    if(senders[0] == 1){
                        if(source == 0){
                            send(msg,"gate$o",0);
                        }
                        if(source == 2){
                            send(msg,"gate$o",1);
                        }
                    }
                    if(senders[0] == 2){
                        if(source == 0){
                            send(msg,"gate$o",1);
                        }
                        if(source == 1){
                            send(msg,"gate$o",0);
                        }
                    }
                    EV <<"file "<<file_index<<": " << files[file_index] << " send. From node:" << senders[0] <<"\n";
                    file_index = file_index + 1;
                }else{
                    EV << "output: " << outputs.size()<< " \n";
                    EV << "finish " <<  " \n";
                    finish();
                }

            }
            if(senders.size()==2){
            if(getIndex() == senders[1] ){
                if(sources.size() > file_index){
                      MyMSG *msg = new MyMSG("new2");
                      std::string temp = sources[files[file_index]];
                      EV << "temp file_index: "<<files[file_index]<<endl;
                      const char *p = temp.data();
                      msg->setData(p);
                      msg->setSource(senders[1]);
                      if(senders[1] == 0){
                          if(source == 1){
                              send(msg,"gate$o",0);
                          }
                          if(source == 2){
                              send(msg,"gate$o",1);
                          }
                      }
                      if(senders[1] == 1){
                          if(source == 0){
                              send(msg,"gate$o",0);
                          }
                          if(source == 2){
                              send(msg,"gate$o",1);
                          }
                      }
                      if(senders[1] == 2){
                          if(source == 0){
                              send(msg,"gate$o",1);
                          }
                          if(source == 1){
                              send(msg,"gate$o",0);
                          }
                      }
                      EV <<"file "<<file_index<<": " << files[file_index] << " send. From node:" << senders[1] <<"\n";
                      file_index = file_index + 1;
                }else{
                    EV << "output: " << outputs.size()<< " \n";
                    EV << "finish " <<  " \n";
                    finish();
                }
            }
            }

    }


}
