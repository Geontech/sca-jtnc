
/*{%extends "pull/resource_base.h"%}*/
/*{%block license%}*/
/*{% from "gpl.cpp" import gplHeader%}*/
${gplHeader(component)}
/*{%endblock%}*/

/*{% block includeExtentions %}*/

// The octave imports make this program GPL.
#include <octave/oct.h>
#include <octave/parse.h>
#include <octave/octave.h>
#include <octave/toplev.h>

#include <boost/filesystem.hpp>
/*{% endblock %}*/

/*{% block extendedPublic %}*/
        int serviceFunction();
        void setCurrentWorkingDirectory(std::string& cwd);
        const octave_value_list _feval(const std::string function, const octave_value_list &functionArguments);
/*{% endblock %}*/

/*{% block extendedPrivate %}*/
        ENABLE_LOGGING
        std::map<std::string, std::vector<double> > inputBuffers;
/*{%if component.ports%}*/
        int buffer(std::string portName, bulkio::InDoublePort* port);
        void populateOutputPacket(
            bulkio::InDoublePort::DataTransferType* outputPacket,
            const octave_value_list&                result,
            const int                               resultIndex);
/*{%endif%}*/
        std::string getLogDir();
        void createDirectoryTree(std::string target_dir);
        void setDiary();
        void flushDiary();
        std::string _diaryFile;
/*{% endblock %}*/

/*{% block extendedProtected%}*/

/*{%if component.ports%}*/
        std::map<std::string, bulkio::InDoublePort::DataTransferType*> inputPackets;
        std::map<std::string, bulkio::InDoublePort::DataTransferType*> outputPackets;

        bulkio::InDoublePort::DataTransferType* createDefaultDataTransferType(std::string&);

/*{%endif%}*/
        virtual int preProcess();
        virtual int postProcess();

        int         _serviceFunctionReturnVal;
        std::string _sriPort;
        double      __sampleRate;
/*{% endblock %}*/
