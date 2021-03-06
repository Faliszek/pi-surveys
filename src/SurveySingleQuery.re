module Single = [%graphql
  {|
    query Form($id: ID!) {
      form(id: $id) {
        _id
        title
        content
        createdAt
        updatedAt
        questions {
            _id
            question
            formType @bsDecoder(fn: "SurveyForm.fallbackToOpenType")
            answers {
                id
                answer
            }
        }
      }}
  |}
];

let use = (~id) => {
  ReasonUrql.Hooks.useQuery(~request=Single.make(~id, ()), ());
};