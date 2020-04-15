module Create = [%graphql
  {|
    mutation SurveyCreate($formInput: FormInputData) {
      createForm(formInput: $formInput) {
        _id
      }
    }
  |}
];

let useCreate = () => {
  ReasonUrql.Hooks.useDynamicMutation(Create.definition);
};

module Edit = [%graphql
  {|
    mutation SurveyEdit($id: ID!, $formInput: FormInputData) {
      updateForm(id: $id, formInput: $formInput) {
        _id
      }
    }
  |}
];

let useEdit = () => {
  ReasonUrql.Hooks.useDynamicMutation(Edit.definition);
};

module Delete = [%graphql
  {|
    mutation SurveyDelete($id: ID!) {
      deleteForm(id: $id)
    }
  |}
];

let useRemove = () => {
  ReasonUrql.Hooks.useDynamicMutation(Delete.definition);
};