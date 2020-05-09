module List = [%graphql
  {|
    query Solutions($page: Int!) {
      addedForms(page: $page) {

    forms {
      _id
      parentId
      questions {
        _id
        question
        answers {
          id
          answer

        }
      }

  }
      }
    }
  |}
];

let use = (~page) => {
  ReasonUrql.Hooks.useQuery(~request=List.make(~page, ()), ());
};