#include "Editor.h"

template <typename FieldType> struct Editor::EditorField {
    bool uses_getter;
    bool uses_setter
    const char *name;
    FieldType *field_ptr;
    FieldType (*getter) ();
    void (*setter) (FieldType);
    
    /** 
     * @brief A constructor taking in a pointer to the field to modify
     * @param name the name/tag of the EditorField
     * @param field_ptr the pointer to the field to modify
     */
    EditorField(const char *name, FieldType *field_ptr) {
        this->name = name;
        uses_getter = false;
        uses_setter = false;
        this->field_ptr = field_ptr;
    }
    /** 
     * @brief A constructor taking in a function pointer to the getter of the field to modify and a pointer to the field itself
     * @param name the name/tag of the EditorField
     * @param getter the pointer to the getter of the field to modify
     * @param field_ptr the pointer to the field to modify
     */
    EditorField(const char *name, FieldType (*getter) (), FieldType *field_ptr) {
        this->name = name;
        uses_getter = true;
        uses_setter = false;
        this->getter = getter;
        this->field_ptr = field_ptr;
    }
    /** 
     * @brief A constructor taking in a function pointer to the setter of the field to modify
     * @param name the name/tag of the EditorField
     * @param setter the pointer to the setter of the field to modify
     * @param field_ptr the pointer to the field to modify
     */
    EditorField(const char *name, void (*setter) (FieldType), FieldType *field_ptr) {
        this->name = name;
        uses_getter = false;
        uses_setter = true;
        this->setter = setter;
        this->field_ptr = field_ptr;
    }
    /** 
     * @brief A constructor taking in two function pointers to the getter and setter of the field to modify
     * @param name the name/tag of the EditorField
     * @param getter the pointer to the getter of the field to modify
     * @param setter the pointer to the setter of the field to modify
     */
    EditorField(const char *name, FieldType (*getter) (), void (*setter) (FieldType)) {
        this->name = name;
        uses_setter = true;
        uses_getter = true;
        this->getter = getter;
        this->setter = setter;
    }

    FieldType get_field_value() { 
        return uses_getter 
            ? getter() 
            : *field_ptr; 
    }

    void set_field_value(FieldType value) {
        if(uses_setter)
            setter(value);
        else
            *field_ptr = value;
    }
};