#ifndef _EDITOR_H
#define _EDITOR_H
#include <unordered_map>

#include "../EngineContext.h"
#include "../Camera.h"

/**
 * @brief Class to handle the Editor interactions
*/
class Editor {
    /** @brief A generic struct representing an in-/output field in the editor.*/
    template <typename FieldType> struct EditorField;
    const std::unordered_map<const char*, EditorField> fields;

    
};

#endif//_EDITOR_H