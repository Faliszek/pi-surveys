module Solve = [%graphql
  {|
    mutation Solve($solutionInput: SolutionInput!) {
      solve(solutionInput: $solutionInput) {
        _id
      }
    }
  |}
];

module AddSolution = [%graphql
  {|
    mutation UpdateForm($formInput: FormInputData) {
      saveForm( formInput: $formInput) {
        _id
      }
    }
  |}
];

let useAdd = () =>
  ReasonUrql.Hooks.useDynamicMutation(AddSolution.definition);

let use = () => {
  ReasonUrql.Hooks.useDynamicMutation(Solve.definition);
};