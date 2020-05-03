module Solve = [%graphql
  {|
    mutation Solve($solutionInput: SolutionInput!) {
      solve(solutionInput: $solutionInput) {
        _id
      }
    }
  |}
];

let use = () => {
  ReasonUrql.Hooks.useDynamicMutation(Solve.definition);
};