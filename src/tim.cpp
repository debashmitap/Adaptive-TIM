//#define HEAD_TRACE
#define HEAD_INFO

#define HEAD_INFO
//#define HEAD_TRACE
#include "sfmt/SFMT.h"
#include "head.h"
#include "memoryusage.h"
#include "graph.h"

void run(TimGraph & m, string dataset, int k, double epsilon, string model, int n_prime){
    cout << "dataset:" << dataset << " k:" << k << " epsilon:"<< epsilon <<   " model:" << model << endl;
    m.k=k;
    if(model=="IC")
        m.setInfuModel(InfGraph::IC);
    else if(model=="LT")
        m.setInfuModel(InfGraph::LT);
    else
        ASSERT(false);

    m.n_prime = n_prime;

    cout<<"Finish Read Graph, Start Influence Maximization"<<endl;
    m.EstimateOPT(epsilon);
    cout<<"Time used: " << Timer::timeUsed[100]/TIMES_PER_SEC << "s" <<endl;

    cout<<"Selected k SeedSet: ";
    for(auto item:m.seedSet)
        cout<< item << " ";
    cout<<endl;

    ofstream seedfile;
    seedfile.open("seed.txt");
    if (!seedfile) {
        cout << "File seeds.txt could not be opened" << endl;
    }
    for (int item:m.seedSet) {
        seedfile << item << endl;
    }
    seedfile.close();
    //cout<<"Estimated Influence: " << m.InfluenceHyperGraph() << endl;
    Counter::show();
}
void parseArg(int argn, char ** argv)
{
    string dataset="";

    double epsilon=0;
    string model="";
    int k=0;
    int n_prime=0;

    for(int i=0; i<argn; i++)
    {
        if(argv[i]==string("-dataset")) dataset=string(argv[i+1])+"/";
        if(argv[i]==string("-epsilon")) epsilon=atof(argv[i+1]);
        if(argv[i]==string("-k")) k=atoi(argv[i+1]);
        if(argv[i]==string("-model")) {
            if(argv[i+1]==string("LT"))
            {
                model=argv[i+1];
            }
            else if(argv[i+1]==string("IC"))
            {
                model=argv[i+1];
            }
            else
                ExitMessage("model should be IC or LT");
        }
        if(argv[i]==string("-n")) n_prime=atoi(argv[i+1]);
    }
    if (dataset=="")
        ExitMessage("argument dataset missing");
    if (k==0)
        ExitMessage("argument k missing");
    if (epsilon==0)
        ExitMessage("argument epsilon missing");
    if (model=="")
        ExitMessage("argument model missing");


    string graph_file;
    if(model=="IC")
        graph_file=dataset + "graph_ic.inf";
    else if(model=="LT")
        graph_file=dataset + "graph_lt.inf";

    TimGraph m(dataset, graph_file);
    run(m, dataset, k ,  epsilon, model, n_prime);
}





int main(int argn, char ** argv)
{
    OutputInfo info(argn, argv);
    parseArg( argn, argv );
}






