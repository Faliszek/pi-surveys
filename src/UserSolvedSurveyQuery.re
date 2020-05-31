module U = [%graphql
  {|
    query UserSolvedSurveyQuery($solution: String) {
      userSolvedSurvey(solution: $solution) {
              _id
       }
    }
  |}
];

let use = solution => {
  ReasonUrql.Hooks.useQuery(
    ~request=U.make(~solution?, ()),
    ~pause=Belt.Option.isSome(solution),
    (),
  );
};