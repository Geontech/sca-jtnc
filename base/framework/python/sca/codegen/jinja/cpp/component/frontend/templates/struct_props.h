
//% extends "pull/struct_props.h"

/*{% block includes %}*/
${super()}
/*{% if 'FrontendTuner' in component.implements %}*/
#include <frontend/fe_tuner_struct_props.h>
/*{% endif %}*/
/*{% endblock %}*/
