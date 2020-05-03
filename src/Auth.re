open AuthContext;

let use = () => React.useContext(context);

module Provider = {
  [@react.component]
  let make = (~children, ~value) => {
    let (auth, setAuth) = React.useState(_ => value);
    let url = ReasonReactRouter.useUrl();

    React.useEffect1(
      () => {
        let token = Dom.Storage.getItem("token", Dom.Storage.localStorage);
        switch (token) {
        | Some(token) => setAuth(auth => {...auth, token: Some(token)})
        | None => ()
        };
        None;
      },
      [||],
    );

    React.useEffect1(
      () => {
        Js.log(auth.token);
        switch (auth.token) {
        | Some(token) =>
          Dom.Storage.setItem("token", token, Dom.Storage.localStorage)
        | None => Dom.Storage.removeItem("token", Dom.Storage.localStorage)
        };

        None;
      },
      [|auth.token|],
    );
    <AuthContext
      value={
        token: auth.token,
        setToken: token => setAuth(auth => {...auth, token}),
      }>
      children
    </AuthContext>;
  };
};