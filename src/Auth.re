open AuthContext;

let use = () => React.useContext(context);

module Provider = {
  [@react.component]
  let make = (~children, ~value) => {
    let (auth, setAuth) = React.useState(_ => value);

    React.useEffect0(() => {
      let token = Dom.Storage.getItem("token", Dom.Storage.localStorage);
      switch (token) {
      | Some(token) =>
        setAuth(auth => {...auth, token: Some(token)});
        ReasonReactRouter.push("/");
      | None => ()
      };
      None;
    });

    React.useEffect1(
      () => {
        Js.log2("Time to save token", auth.token);

        switch (auth.token) {
        | Some(token) =>
          Dom.Storage.setItem("token", token, Dom.Storage.localStorage);
          ReasonReactRouter.push("/");
        | None =>
          ReasonReactRouter.push("/login");
          Dom.Storage.removeItem("token", Dom.Storage.localStorage);
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