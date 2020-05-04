module List = [%graphql
  {|
    query Solutions($page: Int!, $name: String, $email: String, $number: String, $surveyId: String) {
      solutions(page: $page, email:$email, number: $number, name: $name, surveyId: $surveyId) {
        entries {
            _id
            name
            email
            number
            surveyId
        }
        total
      }
    }
  |}
];

let use = (~page, ~name, ~email, ~number, ~surveyId) => {
  ReasonUrql.Hooks.useQuery(
    ~request=List.make(~page, ~name?, ~email?, ~number?, ~surveyId?, ()),
    (),
  );
};