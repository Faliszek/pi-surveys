module Login = [%graphql
  {|
    query Login($email: String!, $password: String!) {
      login(email: $email, password: $password) {
        token
      }
    }
  |}
];

let use = (~email, ~password) => {
  ReasonUrql.Hooks.useQuery(
    ~request=Login.make(~email, ~password, ()),
    ~pause=true,
    (),
  );
};