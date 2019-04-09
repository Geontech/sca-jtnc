
//% extends "pull/resource_base.h"
/*{% block defines %}*/
${super()}
#define BOOL_VALUE_HERE 0
/*{% endblock %}*/

/*{% block extendedPublic %}*/
/*{%   if component.hasmultioutport %}*/
        void matchAllocationIdToStreamId(const std::string allocation_id, const std::string stream_id, const std::string port_name="");
        void removeAllocationIdRouting(const size_t tuner_id);
        void removeStreamIdRouting(const std::string stream_id, const std::string allocation_id="");
/*{%   else %}*/
        void removeAllocationIdRouting(const size_t tuner_id);
/*{%   endif %}*/
/*{%   if 'FrontendTuner' in component.implements %}*/

        virtual CF::Properties* getTunerStatus(const std::string& allocation_id);
        virtual void assignListener(const std::string& listen_alloc_id, const std::string& allocation_id);
        virtual void removeListener(const std::string& listen_alloc_id);
        void frontendTunerStatusChanged(const std::vector<frontend_tuner_status_struct_struct>* oldValue, const std::vector<frontend_tuner_status_struct_struct>* newValue);
/*{%   endif %}*/
/*{% endblock %}*/

/*{% block baseProtectedMembers %}*/
${super()}
/*{% if 'FrontendTuner' in component.implements %}*/
        std::map<std::string, std::string> listeners;
/*{% endif %}*/
/*{% endblock %}*/

/*{% block extendedProtected%}*/
/*{% endblock %}*/
