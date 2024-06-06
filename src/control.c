#include "control.h"

struct control *add_control_to_ctrl_list(struct control *phead, struct control *ctrl_interface)
{
//    struct control *p = phead;

    if (phead == NULL)
    {
        phead = ctrl_interface;

        printf("%s|%s|%d:\n", __FILE__, __FUNCTION__, __LINE__);

        return phead;
    }
    else
    {
        ctrl_interface->next = phead;
        phead = ctrl_interface;

        printf("%s|%s|%d:\n", __FILE__, __FUNCTION__, __LINE__);

        return phead;
    }
    
    return phead;
}
