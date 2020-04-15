module List = [%graphql
  {|
    query Forms($page: Int!) {
      forms(page: $page) {
        forms {
            _id
            title
            content
            creator {
                _id
                name
            }
            createdAt
            updatedAt
        }
        totalForms
      }
    }
  |}
];

let use = (~page) => {
  ReasonUrql.Hooks.useQuery(~request=List.make(~page, ()), ());
};