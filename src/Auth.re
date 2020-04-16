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
        Js.log2("Time to save token", auth.token);

        switch (auth.token, url.path) {
        | (Some(token), ["login"]) =>
          Dom.Storage.setItem("token", token, Dom.Storage.localStorage);
          ReasonReactRouter.push("/");

        | _ => ()
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