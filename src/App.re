open Belt;

// Fetch.;

let makeClient = (~token) =>
  switch (token) {
  | Some(token) =>
    ReasonUrql.Client.make(
      ~requestPolicy=`NetworkOnly,
      ~fetchOptions=
        UrqlClient.FetchOpts(
          Fetch.RequestInit.make(
            ~headers=
              Fetch.HeadersInit.make({"Authorization": "Bearer " ++ token}),
            (),
          ),
        ),
      ~url="http://localhost:3000/graphql",
      (),
    )
  | None => ReasonUrql.Client.make(~url="http://localhost:3000/graphql", ())
  };

module App = {
  [@react.component]
  let make = () => {
    let url = ReasonReactRouter.useUrl();

    let {token}: AuthContext.t = Auth.use();

    let (client, setClient) = React.useState(() => makeClient(~token));

    React.useEffect1(
      () => {
        let client = makeClient(~token);
        setClient(_ => client);
        None;
      },
      [|token|],
    );
    Js.log2(Option.isSome(token), url.path);
    <ReasonUrql.Provider value=client>
      {switch (Option.isSome(token), url.path) {
       | (false, ["surveys", id]) => <SurveySolve id />
       | (false, _) => <LoginView />

       | (true, ["login"])
       | (true, ["surveys"])
       | (true, []) => <SurveyListView />

       | (_, ["create-survey"]) => <SurveyCreate />

       | (true, ["surveys", id]) => <SurveySingleView id />

       | (true, ["results"]) => <ResultsListView />
       | (true, _) => <SurveyListView />
       | _ => "No match"->React.string
       }}
    </ReasonUrql.Provider>;
  };
};

[@react.component]
let make = () => {
  <Auth.Provider value=AuthContext.initialState>
    <Notification.Provider> <App /> </Notification.Provider>
  </Auth.Provider>;
};