open Belt;

// Fetch.;

let makeClient = (~token) =>
  switch (token) {
  | Some(token) =>
    ReasonUrql.Client.make(
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
        Js.log2("update new client", client);
        None;
      },
      [|token|],
    );

    Js.log(token);

    <ReasonUrql.Provider value=client>
      {switch (Option.isSome(token), url.path) {
       | (true, ["create-survey"]) => <SurveyCreate />
       | (true, ["surveys"])
       | (true, []) => <SurveyListView />
       | (true, ["surveys", id]) => <SurveySingleView id />

       | (true, ["results"]) => <ResultsListView />
       | (false, ["login"]) => <LoginView />
       | _ => React.null
       }}
    </ReasonUrql.Provider>;
  };
};

[@react.component]
let make = () => {
  <Auth.Provider value=AuthContext.initialState>
    <Notification.Provider value=NotificationContext.initialState>
      <App />
    </Notification.Provider>
  </Auth.Provider>;
};